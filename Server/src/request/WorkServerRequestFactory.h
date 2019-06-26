#ifndef __WORKSERVERREQUESTFACTORY_H__
#define __WORKSERVERREQUESTFACTORY_H__

#include <Poco/Net/HTTPRequestHandlerFactory.h>


class RouteMap;

class WorkServerRequestFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
        WorkServerRequestFactory(RouteMap * routeMap);
        Poco::Net::HTTPRequestHandler* createRequestHandler(
                const Poco::Net::HTTPServerRequest& request) override;
private:
        RouteMap * _RouteMap;
};



#endif // !__WORKSERVERREQUESTFACTORY_H__