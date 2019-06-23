#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "WorkServerRequestFactory.h"
#include "controller/HomeController.h"
#include "RouteMap.h"

WorkServerRequestFactory::WorkServerRequestFactory(RouteMap * routeMap) 
    : _RouteMap(routeMap) {
}

Poco::Net::HTTPRequestHandler* WorkServerRequestFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
{
    auto context = _RouteMap->GetWorkContext(
        request.getURI(),
        request.getMethod()
    );

    if(!context)
        return nullptr;

    // if (request.getURI() == "/Home/Index" && 
    //     request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
    //     return new HomeController(_Context);
    // }
    return nullptr;
}