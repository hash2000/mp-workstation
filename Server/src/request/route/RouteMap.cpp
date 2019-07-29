#include <stdafx.h>

#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/StringTokenizer.h>
#include <Poco/StreamCopier.h>
#include <Poco/FileStream.h>
#include <Poco/DirectoryIterator.h>

#include "RouteMap.h"
#include "RouteMapStatistic.h"

#include <list>
#include <string>
#include <sstream>



void RouteMap::Initialize()
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);

    _DefaultRoute = "/Areas/Default/Home/Index";

    _LayoutTemplates.Initialize();

    InitializeContentTypes();

}

void RouteMap::InitializeContentTypes()
{
    _ContentTypesByExtensions["ico"] = "image/x-icon";
    _ContentTypesByExtensions["gif"] = "image/gif";
    _ContentTypesByExtensions["jpeg"] = "image/jpeg";
    _ContentTypesByExtensions["png"] = "image/png";
    _ContentTypesByExtensions["svg"] = "image/svg+xml";
    _ContentTypesByExtensions["js"] = "application/javascript";
    _ContentTypesByExtensions["json"] = "application/json";
}

WorkContext * RouteMap::GetWorkContext(
    const std::string & uri,
    const std::string & method)
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);
    RouteMapStatistic statistic;

    // Параметр context->_UseCount, при создании должен быть равен 1, или 
    //  при повторном использовании должен быть увеличен на единицу.
    // Это нужно сделать внутри критической секции, а уменьшение счётчика,
    //  можно вызвать за вне критической секции
    
    std::string route = method + ":";
    std::string routeUri;

    if (uri.empty() || uri == "/") {
        routeUri = _DefaultRoute; 
    }
    else {
        routeUri = uri;
    }

    route += routeUri;

    Poco::Path pathinfo("Web/www" + routeUri);
    pathinfo = pathinfo.makeAbsolute();
    auto isAreaView = false;
    auto extension = pathinfo.getExtension();
    if (extension.empty() || extension == "html") {
        pathinfo.setExtension("html");
        extension = pathinfo.getExtension();
        isAreaView = true;
    }

    statistic.SetRoute(route);
    statistic.IsAreaView(isAreaView);
    
    Poco::File fileinfo(pathinfo);
    if (!fileinfo.exists()) {
        statistic.AppendErrorMessage(pathinfo.toString());
        statistic.AppendErrorMessage("file not found");
        return nullptr;
    }

    Poco::LocalDateTime lastFileModified(fileinfo.getLastModified());
    statistic.SetSourceModifiedDate(lastFileModified);

    // если файл найден и дата его обновления больше чем при последнем чтении
    //  тогда его требуется перезагрузить
    auto routeIterator = _Routes.find(route);
    if (routeIterator != _Routes.end()) {
        statistic.SetCacheState(RouteMapStatistic::CacheUse);
        // перезагрузить данные можно только если контекст никемне занят
        if (routeIterator->second->_UseCount == 0) {
            if (routeIterator->second->_ReadTime < lastFileModified) {
                statistic.SetCacheState(RouteMapStatistic::CacheUpdate);
                if (routeIterator->second->_Layout) {
                    routeIterator->second->_Layout->Initialize(routeIterator->second, &_LayoutTemplates);
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
    context->_UseCount = 1;

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

    auto contentTypeIterator = _ContentTypesByExtensions.find(extension);
    if (contentTypeIterator != _ContentTypesByExtensions.end()) {
	    context->_ContentType = contentTypeIterator->second;
    }

    _Routes[route] = context;
    return context;
}

