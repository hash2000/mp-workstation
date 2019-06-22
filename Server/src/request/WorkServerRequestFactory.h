#ifndef __WORKSERVERREQUESTFACTORY_H__
#define __WORKSERVERREQUESTFACTORY_H__

#include <Poco/Net/HTTPRequestHandlerFactory.h>


class WorkContext;

class WorkServerRequestFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
        WorkServerRequestFactory(WorkContext * context);
        Poco::Net::HTTPRequestHandler* createRequestHandler(
                const Poco::Net::HTTPServerRequest& request) override;
private:
        WorkContext * _Context;
};



#endif // !__WORKSERVERREQUESTFACTORY_H__