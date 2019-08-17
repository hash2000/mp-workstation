#include <stdafx.h>

#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/StringTokenizer.h>
#include <Poco/StreamCopier.h>
#include <Poco/FileStream.h>
#include <Poco/DirectoryIterator.h>
#include <Poco/Net/HTTPRequest.h>

#include "RouteMap.h"
#include "RouteMapStatistic.h"

#include "../controller/Admin/UserGETController.h"
#include "../controller/System/Objects/ObjectsGetController.h"
#include "../controller/System/Objects/ObjectsAddController.h"
#include "../controller/System/ObjectTypes/ObjectTypesGetController.h"

#include <list>
#include <string>
#include <sstream>



void RouteMap::Initialize()
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);

    _DefaultRoute = "/Areas/Default/Home/Index";
    _MimeTypes = new Poco::Util::PropertyFileConfiguration(
        "Web/MIME/types.properties");

    RegisterRouteUnsafe("/Admin/Users/Get", 
        Poco::Net::HTTPRequest::HTTP_GET, new UserGETController);

    RegisterRouteUnsafe("/System/ObjectTypes/Get", 
        Poco::Net::HTTPRequest::HTTP_GET, new ObjectTypesGetController);

    RegisterRouteUnsafe("/System/Objects/Get", 
        Poco::Net::HTTPRequest::HTTP_GET, new ObjectsGetController);
    RegisterRouteUnsafe("/System/Objects/Add", 
        Poco::Net::HTTPRequest::HTTP_POST, new ObjectsAddController);

    _LayoutTemplates.Initialize();
}

void RouteMap::RegisterRoute(
    const std::string & path, 
    const std::string & method, 
    IBaseController * controller) 
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);
    RegisterRouteUnsafe(path, method, controller);
}

void RouteMap::RegisterRouteUnsafe(
    const std::string & path, 
    const std::string & method, 
    IBaseController * controller)
{
    std::string route = method + ":" + path; 

    auto & app = Poco::Util::Application::instance();
    auto found = _Routes.find(route);
    if (found != _Routes.end()) {
        app.logger().error("RouteMap::RegisterRoute: Route [" + route + 
            "] allready registered");
        return;
    }

    app.logger().information("RouteMap::RegisterRoute: Route [" + route + 
        "] registered");

    auto context = new WorkContext; 
    context->_Controller = controller;
    _Routes[route] = context;
}

void RouteMap::ReadRequestParameters(
        WorkContext * context,
        Poco::Net::HTTPServerRequest & request)
{
    
    context->_RequestParameters.reset();

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
        Poco::URI uri(request.getURI());
        auto requestQuery = uri.getQuery();

        context->_RequestParameters.reset(new Poco::JSON::Object);
        
        // Обработка запроса        
        Poco::StringTokenizer paramTokens(requestQuery, "&");
        for (auto paramIt = paramTokens.begin(), paramEnd = paramTokens.end(); paramIt != paramEnd; paramIt ++) {
            Poco::StringTokenizer keyValueTokens(*paramIt, "=");
            if (keyValueTokens.count() != 2) {            
                continue;
            }
            
            auto key = keyValueTokens[0];
            auto value = keyValueTokens[1];
            context->_RequestParameters->set(key, value);
        }

    }
    else {

        if (request.getContentType() == "application/json") {
            Poco::JSON::Parser pareser;
            auto result = pareser.parse(request.stream());
            if (result.type() == typeid(Poco::JSON::Object::Ptr)) {
                context->_RequestParameters.reset(result.extract<Poco::JSON::Object::Ptr>());
            }
        }
    }   

}

WorkContext * RouteMap::GetWorkContext(
    Poco::Net::HTTPServerRequest& request)
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);
    RouteMapStatistic statistic;

    // Параметр context->_UseCount, при создании должен быть равен 1, или 
    //  при повторном использовании должен быть увеличен на единицу.
    // Это нужно сделать внутри критической секции, а уменьшение счётчика,
    //  можно вызвать за вне критической секции
    Poco::URI uri(request.getURI());
    std::string method = request.getMethod(); 
    std::string path = uri.getPath();
    std::string route = method + ":";
    std::string routeUri;

    if (path.empty() || path == "/") {
        routeUri = _DefaultRoute; 
    }
    else {
        routeUri = path;
    }

    route += routeUri;
    statistic.SetRoute(route);


    auto routeIterator = _Routes.find(route);
    if (routeIterator != _Routes.end()) {

        ReadRequestParameters(routeIterator->second, request);

        // если это предварительно зарегистрированный котроллер,
        //  тогда нужно сразу вернуть этот контекст
        if (routeIterator->second->_Controller) {
            // возможно для контроллеров не нужно считать ссылки
            //  дальше будет видно
            // routeIterator->second->_UseCount ++;
            statistic.SetCacheState(RouteMapStatistic::CacheController);
            return routeIterator->second;   
        }
    }

    Poco::Path pathinfo("Web/www" + routeUri);
    pathinfo = pathinfo.makeAbsolute();
    auto isAreaView = false;
    auto extension = pathinfo.getExtension();
    if (extension.empty() || extension == "html") {
        pathinfo.setExtension("html");
        extension = pathinfo.getExtension();
        isAreaView = true;
    }

    statistic.IsAreaView(isAreaView);
    
    Poco::File fileinfo(pathinfo);
    if (!fileinfo.exists()) {
        statistic.AppendErrorMessage(pathinfo.toString());
        statistic.AppendErrorMessage("file not found");
        return nullptr;
    }

    Poco::LocalDateTime lastFileModified(fileinfo.getLastModified());
    statistic.SetSourceModifiedDate(lastFileModified);

    if (routeIterator != _Routes.end()) {
        statistic.SetCacheState(RouteMapStatistic::CacheUse);
        statistic.SetCacheModifiedDate(routeIterator->second->_ReadTime);
        statistic.SetUseCount(routeIterator->second->_UseCount);
        // перезагрузить данные можно только если контекст никем не занят
        if (routeIterator->second->_UseCount == 0) {

            // если файл найден и дата его обновления больше чем при последнем чтении
            //  тогда его требуется перезагрузить
            if (routeIterator->second->_ReadTime < lastFileModified) {
                statistic.SetCacheState(RouteMapStatistic::CacheUpdate);

                if (routeIterator->second->_Layout) {
                    routeIterator->second->_Layout->Initialize(routeIterator->second, &_LayoutTemplates);
                }
                else {
                    Poco::FileInputStream stream;
                    stream.open(routeIterator->second->_Path.toString(), std::ios::in);
                    if (stream.bad()) {
                        statistic.AppendErrorMessage(pathinfo.toString());
                        statistic.AppendErrorMessage("bad file");
                    }    
                    else {
                        routeIterator->second->_FileBufferSize = fileinfo.getSize();
                        routeIterator->second->_ReadTime = lastFileModified;
                        routeIterator->second->_FileBuffer.clear();
                        Poco::StreamCopier::copyToString(stream, routeIterator->second->_FileBuffer);
                    }                   
                }                
            }
        }
        
        routeIterator->second->_UseCount ++;
        return routeIterator->second;
    }

    statistic.SetCacheState(RouteMapStatistic::CacheLoad);

    auto context = new WorkContext;
    context->_Path = pathinfo;
    context->_ReadTime = lastFileModified;
    context->_Layout = nullptr;
    context->_Controller = nullptr;
    context->_UseCount = 1;

    ReadRequestParameters(context, request);

    if (isAreaView) {
        // если isAreaView, значит это шаблон контента, который встаивается в Layout
        context->_Layout = new LayoutBuilder;
        context->_Layout->Initialize(context, &_LayoutTemplates);
    }
    else {
        // иначе это файл который нужно отправить 
        Poco::FileInputStream stream;
        stream.open(context->_Path.toString(), std::ios::in);
        if (stream.bad()) {
            statistic.AppendErrorMessage(pathinfo.toString());
            statistic.AppendErrorMessage("bad file");
        }    
        else {
            context->_FileBufferSize = fileinfo.getSize();
            Poco::StreamCopier::copyToString(stream, context->_FileBuffer);
        }
    }

    context->_ContentType = _MimeTypes->getString("extension." + extension, "");

    _Routes[route] = context;

    return context;
}

