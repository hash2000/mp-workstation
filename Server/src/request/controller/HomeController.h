#ifndef __HOMECONTROLLER_H__
#define __HOMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>

class WorkContext;

class HomeController: public Poco::Net::HTTPRequestHandler
{
public:
    HomeController(WorkContext * context);

    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;

private:
    WorkContext * _Context;
};


#endif // !__HOMECONTROLLER_H__