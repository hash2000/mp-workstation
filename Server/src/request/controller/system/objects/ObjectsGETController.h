#ifndef __ObjectsGETController_H__
#define __ObjectsGETController_H__

#include "../../interface/IBaseController.h"

class ObjectsGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments) override;
};

#endif // !__ObjectsGETController_H__