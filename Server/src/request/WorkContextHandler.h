#ifndef __WorkContextHandler_H__
#define __WorkContextHandler_H__

#include <Poco/Net/HTTPRequestHandler.h>

class RouteMap;
class WorkContext;
class DatabaseManager;


class WorkContextHandler: public Poco::Net::HTTPRequestHandler
{
public:
    WorkContextHandler(RouteMap * routeMap, 
        DatabaseManager * dbManager);
    virtual ~WorkContextHandler() ;

    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;

protected:
    WorkContext * _Context = nullptr;
    RouteMap * _RouteMap;
    DatabaseManager * _DbManager;
};

#endif // !__WorkContextHandler_H__