#ifndef __HOMECONTROLLER_H__
#define __HOMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>

class HomeController: public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;
};


#endif // !__HOMECONTROLLER_H__