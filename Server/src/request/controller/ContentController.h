#ifndef __CONTENTCONTROLLER_H__
#define __CONTENTCONTROLLER_H__

#include "BaseController.h"

class WorkContext;

class ContentController: public BaseController
{
public:
    ContentController(WorkContext * context);

    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;

};

#endif // !__CONTENTCONTROLLER_H__
