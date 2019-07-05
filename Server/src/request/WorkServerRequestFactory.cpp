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
    if(!context) {
        printf("Error: WorkServerRequestFactory::createRequestHandler %s %s undefined\n",
            method.c_str(), uri.c_str());
        return nullptr;
    }

    printf("%s %s required\n", method.c_str(), uri.c_str());

    return new WorkContextController(context);
}