#include <stdafx.h>
#include "RouteMap.h"
#include "../controller/AreaViewController.h"

#include <Poco/DirectoryIterator.h>
#include <list>
#include <string>
#include <sstream>

void RouteMap::Initialize()
{
    RegisterAreaViewRoute("Home", "Index", "GET", [] (WorkContext* context) {
        return new AreaViewController(context);
    });


}

WorkContext * RouteMap::GetWorkContext(
    const std::string & uri,
    const std::string & method) const
{
    auto route = method + ":" + uri;
    auto it = _AreaViewRoutes.find(route);
    if (it == _AreaViewRoutes.end())
        return nullptr;
    return it->second;
}

void RouteMap::RegisterAreaViewRoute(
    const std::string & controller,
    const std::string & action,
    const std::string & method,
    WorkContext::ControllerFactoryHandler handler)
{
    auto route = method + ":/" + controller + "/" + action;
    if(_AreaViewRoutes.find(route) != _AreaViewRoutes.end()) {
        throw new Poco::Exception("RouteMap::RegisterRoute [" + route + " ] allready defined");
        return;
    }

    std::stringstream path;
    path << "/Web/Areas/" << controller 
        << "/Views/" << method << "/" << action << ".html";

    auto context = new WorkContext;
    context->_relativePath = path.str();
    context->_ControllerFactory = handler;
    context->_Layout = new LayoutBuilder;
    context->_Layout->Initialize();

    _AreaViewRoutes[route] = context;
}