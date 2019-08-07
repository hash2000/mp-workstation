#ifndef __WorkServerRequestFactory_H__
#define __WorkServerRequestFactory_H__

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



#endif // !__WorkServerRequestFactory_H__