#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>


#include "WorkServerRequestFactory.h"
#include "RouteMap.h"

#include "content/ContentManager.h"


WorkServerRequestFactory::WorkServerRequestFactory(
    RouteMap * routeMap, 
    ContentManager * content) 
    : _RouteMap(routeMap)
    , _Content(content) {
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

    printf("%s %s undefined\n", method.c_str(), uri.c_str());

    return context->_ControllerFactory(context);
}