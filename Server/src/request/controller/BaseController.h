#ifndef __BASECONTROLLER_H__
#define __BASECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>

class WorkContext;

class BaseController: public Poco::Net::HTTPRequestHandler
{
public:
    BaseController(WorkContext * context)
        : _Context(context) {
    }
protected:
    WorkContext * _Context;
};

#endif // !__BASECONTROLLER_H__