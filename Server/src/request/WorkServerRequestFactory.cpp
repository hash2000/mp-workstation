#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>

#include "WorkServerRequestFactory.h"
#include "WorkContextHandler.h"


WorkServerRequestFactory::WorkServerRequestFactory(RouteMap * routeMap,
                DatabaseManager * dbManager) 
    : _RouteMap(routeMap)
    , _DbManager(dbManager) {
}

Poco::Net::HTTPRequestHandler* WorkServerRequestFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
{   
    return new WorkContextHandler(_RouteMap, _DbManager);
}