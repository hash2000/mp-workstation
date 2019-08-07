#ifndef __OBJECTSGETCONTROLLER_H__
#define __OBJECTSGETCONTROLLER_H__

#include "../../interface/IBaseController.h"

class ObjectsGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments) override;
};

#endif // !__OBJECTSGETCONTROLLER_H__