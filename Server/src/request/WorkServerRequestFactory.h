#ifndef __WORKSERVERREQUESTFACTORY_H__
#define __WORKSERVERREQUESTFACTORY_H__

#include <Poco/Net/HTTPRequestHandlerFactory.h>


class RouteMap;
class DatabaseManager;

class WorkServerRequestFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
        WorkServerRequestFactory(RouteMap * routeMap,
                DatabaseManager * dbManager);
        Poco::Net::HTTPRequestHandler* createRequestHandler(
                const Poco::Net::HTTPServerRequest& request) override;
private:
        RouteMap * _RouteMap;
        DatabaseManager * _DbManager;
};



#endif // !__WORKSERVERREQUESTFACTORY_H__