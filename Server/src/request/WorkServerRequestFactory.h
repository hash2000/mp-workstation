#ifndef __WORKSERVERREQUESTFACTORY_H__
#define __WORKSERVERREQUESTFACTORY_H__

#include <Poco/Net/HTTPRequestHandlerFactory.h>


class RouteMap;
class ContentManager;

class WorkServerRequestFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
        WorkServerRequestFactory(RouteMap * routeMap, ContentManager * content);
        Poco::Net::HTTPRequestHandler* createRequestHandler(
                const Poco::Net::HTTPServerRequest& request) override;
private:
        RouteMap * _RouteMap;
        ContentManager * _Content;
};



#endif // !__WORKSERVERREQUESTFACTORY_H__