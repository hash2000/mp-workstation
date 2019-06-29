#include <stdafx.h>
#include "RouteMap.h"
#include "../controller/AreaViewController.h"
#include "../controller/ContentController.h"

#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/StringTokenizer.h>
#include <Poco/FileStream.h>

#include <list>
#include <string>
#include <sstream>

const std::string RouteMap::DefaultArea = "Home";
const std::string RouteMap::DefaultController = "Home";
const std::string RouteMap::DefaultAction = "Index";
const std::string RouteMap::DefaultActionExtension = ".html";


void RouteMap::Initialize()
{

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

    auto context = GetContentWorkContext(uri, method);
    if (context)
        return context;

    context = GetAreaViewWorkContext(uri, method);
    if (context)
        return context;
    
    return nullptr;
}

