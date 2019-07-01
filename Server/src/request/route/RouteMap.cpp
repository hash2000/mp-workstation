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
                continue;
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

            }
        }
    }
}

WorkContext * RouteMap::GetContentWorkContext(
        const std::string & uri, 
        const std::string & method)
{    
    auto route = method + ":" + uri;
    auto it = _ContentRoutes.find(route);
    if (it != _ContentRoutes.end())
        return it->second;

    auto filePath = "Web/Content" + uri;
    auto file = Poco::File(filePath);
    if (!file.exists())
        return nullptr;
    if (!file.canRead() || file.isHidden())
        return nullptr;

    auto context = new WorkContext;
    context->_RelativePath = file.path();
    context->_Layout = nullptr;
    context->_ControllerFactory = [] (WorkContext * context) {
        return new ContentController(context);
    };

    _ContentRoutes[route] = context;

    return context;
}

WorkContext * RouteMap::GetAreaViewWorkContext(
        const std::string & uri, 
        const std::string & method)
{
    auto route = method + ":" + uri;
    auto it = _AreaViewRoutes.find(route);
    if (it != _AreaViewRoutes.end())
        return it->second;

    Poco::StringTokenizer routeTokens(uri, "/", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
    auto routeTokensCount = routeTokens.count();
    if (routeTokensCount > 3) {
        return nullptr;
    }

    std::string area, controller,
        action;

    switch(routeTokensCount) {
        case 3:
            area = routeTokens[0];
            controller = routeTokens[1];
            action = routeTokens[2];
            break;
        case 2:
            area = DefaultArea;
            controller = routeTokens[0];
            action = routeTokens[1];
            break;
        case 1:
            area = DefaultArea;
            controller = DefaultController;
            action = routeTokens[0];
            break;
        case 0:
            area = DefaultArea;
            controller = DefaultController;
            action = DefaultAction;
            break;
    }

    std::stringstream path;
    path << "Web/Areas/" << area << "/Views/" << controller 
        << "/" << method << "/" << action << DefaultActionExtension;

    auto filePath = path.str();
    auto file = Poco::File(filePath);
    if (!file.exists())
        return nullptr;
    if (!file.canRead() && !file.isHidden())
        return nullptr;

    auto context = new WorkContext;
    context->_RelativePath = file.path();
    context->_ControllerFactory = [] (WorkContext * context) {
        return new AreaViewController(context);
    };
    context->_Layout = new LayoutBuilder;
    context->_Layout->Initialize(context);

    _AreaViewRoutes[route] = context;

    return context;
}

WorkContext * RouteMap::GetWorkContext(
    const std::string & uri,
    const std::string & method)
{
    Poco::Mutex::ScopedLock lockScope(_RoutesLock);

    // auto context = GetContentWorkContext(uri, method);
    // if (context)
    //     return context;

    // context = GetAreaViewWorkContext(uri, method);
    // if (context)
    //     return context;
    
    Poco::StringTokenizer routeTokens(uri, "/", Poco::StringTokenizer::TOK_IGNORE_EMPTY);
    auto routeTokensCount = routeTokens.count();
    if (routeTokensCount == 0) {
        // стандартный путь Areas/Home/Views/Home/GET/Index.html

    }


    return nullptr;
}

