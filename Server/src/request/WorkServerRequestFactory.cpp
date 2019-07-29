#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "WorkServerRequestFactory.h"

#include "route/RouteMap.h"
#include "controller/WorkContextController.h"


WorkServerRequestFactory::WorkServerRequestFactory(RouteMap * routeMap) 
    : _RouteMap(routeMap) {
}

Poco::Net::HTTPRequestHandler* WorkServerRequestFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
{    
    auto uri = request.getURI();
    auto method = request.getMethod();
    auto context = _RouteMap->GetWorkContext(uri, method);
    if (!context) {
        return nullptr;
    }

    return new WorkContextController(context);
}