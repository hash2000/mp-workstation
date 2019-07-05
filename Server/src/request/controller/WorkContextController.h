#ifndef __WORKCONTEXTCONTROLLER_H__
#define __WORKCONTEXTCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>

class WorkContext;

class WorkContextController: public Poco::Net::HTTPRequestHandler
{
public:
    WorkContextController(WorkContext * context)
        : _Context(context) {
    }

    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;

protected:
    WorkContext * _Context;
};

#endif // !__WORKCONTEXTCONTROLLER_H__