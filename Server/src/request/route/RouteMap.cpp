#include <stdafx.h>
#include "RouteMap.h"
#include "../controller/AreaViewController.h"
#include "../controller/ContentController.h"

#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/StringTokenizer.h>
#include <Poco/FileStream.h>
#include <Poco/DirectoryIterator.h>

#include <list>
#include <string>
#include <sstream>

const std::string RouteMap::DefaultArea = "Home";
const std::string RouteMap::DefaultController = "Home";
const std::string RouteMap::DefaultAction = "Index";
const std::string RouteMap::DefaultActionExtension = ".html";


void RouteMap::Initialize()
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);

    _DefaultRoute = "Areas/Default/Home/Index";

    InitializeContentTypes();

    auto basePath = Poco::Path("Web/Areas/");
    std::list<Poco::Path> paths;
    paths.push_back(basePath);

    for(auto path : paths) 
    {
        for(Poco::DirectoryIterator it(path), _last_path; it != _last_path; it ++) {
            Poco::Path pathinfo(it->path());
            if (Poco::File(pathinfo).isDirectory()) {
                // если это директория, то сохраняю путь и уровень относительно 
                //  базовой папки
                paths.push_back(pathinfo);
            }
            else {
                // путь относительно базовой папки может содержать файлы 
                //  только на третьем уровне и выше
                int pathDepth = pathinfo.depth();
                int basePathDepth = basePath.depth();
                if (pathDepth - basePathDepth < 2) {
                    printf("Warning (ignore) RouteMap::Initialize. "
                        "Relative to the directory Web/Areas/, "
                        "files can only be on the third nesting level\n%s\n",
                        pathinfo.toString().c_str());
                    continue;
                }

                // все файлы по шаблону Web/Areas/[Area name]/[Controller name]/[File name]
                //  добавляются в маршрут GET:[Area name]/[Controller name]/[File name] 
                //  если расширения нет то используется .html

                std::string route = "GET:";
                for(int i = basePathDepth; i < pathDepth; i++) {
                    route += "/" + pathinfo[i];
                }

                auto fileName = pathinfo.getFileName();
                auto fileExtension = pathinfo.getExtension();
                if(fileExtension == "html") {
                    fileName = fileName.substr(0, fileName.size() - fileExtension.size() - 1);
                }

                route += "/" + fileName;

                auto context = new WorkContext;
                context->_Path = pathinfo;
                context->_Layout = new LayoutBuilder;
                context->_Layout->Initialize(context);
                //MakeContentType(context);

                _Routes[route] = context;


            } // !if
        } // !for(DirectoryIterator)
    } // !for(path)
}

void RouteMap::InitializeContentTypes()
{
    _ContentTypesByExtensions["ico"] = "image/x-icon";
    _ContentTypesByExtensions["gif"] = "image/gif";
    _ContentTypesByExtensions["jpeg"] = "image/jpeg";
    _ContentTypesByExtensions["png"] = "image/png";
    _ContentTypesByExtensions["svg"] = "image/svg+xml";
}

WorkContext * RouteMap::GetWorkContext(
    const std::string & uri,
    const std::string & method)
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);
    
    std::string route = method + ":";
    std::string routeUri;

    if (uri.empty() || uri == "/") {
        routeUri = _DefaultRoute;
    }
    else {
        routeUri = uri;
    }

    route += routeUri;

    auto routeIterator = _Routes.find(route);
    if (routeIterator != _Routes.end())
        return routeIterator->second;

    Poco::Path pathinfo(routeUri);
    pathinfo = pathinfo.makeAbsolute();

    auto context = new WorkContext;
    context->_Path = pathinfo;
    context->_Layout = new LayoutBuilder;
    context->_Layout->Initialize(context);

    auto extension = context->_Path.getExtension();
    auto contentTypeIterator = _ContentTypesByExtensions.find(extension);
    if (contentTypeIterator != _ContentTypesByExtensions.end()) {
	    context->_ContentType = contentTypeIterator->second;
    }

    return context;
}

