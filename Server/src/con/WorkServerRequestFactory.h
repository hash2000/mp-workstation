#ifndef __WORKSERVERREQUESTFACTORY_H__
#define __WORKSERVERREQUESTFACTORY_H__

#include <Poco/Net/HTTPRequestHandlerFactory.h>



class WorkServerRequestFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(
        const Poco::Net::HTTPServerRequest& request) override;
};



#endif // !__WORKSERVERREQUESTFACTORY_H__