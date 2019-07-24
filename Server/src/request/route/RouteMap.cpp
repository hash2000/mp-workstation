#include <stdafx.h>

#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/StringTokenizer.h>
#include <Poco/FileStream.h>
#include <Poco/DirectoryIterator.h>

#include "RouteMap.h"

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

    Poco::File fileinfo(pathinfo);
    if (!fileinfo.exists()) {
        return nullptr;
    }

    Poco::LocalDateTime lastFileModified(fileinfo.getLastModified());

    // если файл найден и дата его обновления больше чем при последнем чтении
    //  тогда его требуется перезагрузить
    auto routeIterator = _Routes.find(route);
    if (routeIterator != _Routes.end()) {
        // перезагрузить данные можно только если контекст никемне занят
        if (routeIterator->second->_UseCount == 0) {
            if (routeIterator->second->_Layout && routeIterator->second->_ReadTime < lastFileModified) {
                routeIterator->second->_Layout->Initialize(routeIterator->second, &_LayoutTemplates);
            }
        }
        routeIterator->second->_UseCount ++;
        return routeIterator->second;
    }

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
        context->_FileStream.open(context->_Path.toString(), std::ios::in);
        context->_FileStreamSize = fileinfo.getSize();
        if (context->_FileStream.bad()) {
            printf("Warning: Bad file %s\n", context->_Path.toString().c_str());
        }
    }

    auto contentTypeIterator = _ContentTypesByExtensions.find(extension);
    if (contentTypeIterator != _ContentTypesByExtensions.end()) {
	    context->_ContentType = contentTypeIterator->second;
    }

    return context;
}

