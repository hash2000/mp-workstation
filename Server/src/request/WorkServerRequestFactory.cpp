#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "WorkServerRequestFactory.h"

#include "route/RouteMap.h"
#include "controller/WorkContextController.h"


WorkServerRequestFactory::WorkServerRequestFactory(RouteMap * routeMap,
                DatabaseManager * dbManager) 
    : _RouteMap(routeMap)
    , _DbManager(dbManager) {
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

    context->_DbManager = _DbManager;

    return new WorkContextController(context);
}