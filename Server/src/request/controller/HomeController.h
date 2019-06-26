#ifndef __HOMECONTROLLER_H__
#define __HOMECONTROLLER_H__

#include "BaseController.h"

class WorkContext;

class HomeController: public BaseController
{
public:
    HomeController(WorkContext * context);

    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;

};


#endif // !__HOMECONTROLLER_H__