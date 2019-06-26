#ifndef __AREAVIEWCONTROLLER_H__
#define __AREAVIEWCONTROLLER_H__

#include "BaseController.h"

class WorkContext;

class AreaViewController: public BaseController
{
public:
    AreaViewController(WorkContext * context);

    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;

};


#endif // !__AREAVIEWCONTROLLER_H__