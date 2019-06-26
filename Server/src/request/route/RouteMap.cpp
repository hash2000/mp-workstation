#include <stdafx.h>
#include "RouteMap.h"
#include "../controller/HomeController.h"

#include <Poco/DirectoryIterator.h>
#include <list>
#include <string>

void RouteMap::Initialize()
{
    RegisterRoute("Home", "Index", "GET", [] (WorkContext* context) {
        return new HomeController(context);
    });
}

WorkContext * RouteMap::GetWorkContext(
    const std::string & uri,
    const std::string & method) const
{
    auto route = method + ":" + uri;
    auto it = _Routes.find(route);
    if (it == _Routes.end())
        return nullptr;
    return it->second;
}

void RouteMap::RegisterRoute(
    const std::string & controller,
    const std::string & action,
    const std::string & method,
    WorkContext::ControllerFactoryHandler handler)
{
    auto route = method + ":/" + controller + "/" + action;
    if(_Routes.find(route) != _Routes.end()) {
        throw new Poco::Exception("RouteMap::RegisterRoute [" + route + " ] allready defined");
        return;
    }

    auto context = new WorkContext;
    context->_Controller = controller;
    context->_Action = action;
    context->_Method = method;
    context->_ControllerFactory = handler;
    context->_Layout = new LayoutBuilder;
    context->_Layout->Initialize();

    _Routes[route] = context;
}