#include <stdafx.h>
#include "RouteMap.h"

void RouteMap::Initialize()
{
    RegisterRoute("/Home/Index", "GET");
}

const WorkContext * RouteMap::GetWorkContext(
    const std::string & uri, const std::string & method) const
{
    auto route = method + ":" + uri;
    auto it = _Routes.find(route);
    if (it == _Routes.end())
        return nullptr;
    return it->second;
}

void RouteMap::RegisterRoute(
    const std::string & uri, const std::string & method)
{
    auto route = method + ":" + uri;
}