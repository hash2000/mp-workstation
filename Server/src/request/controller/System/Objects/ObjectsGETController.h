#ifndef __ObjectsGETController_H__
#define __ObjectsGETController_H__

#include "../../IBaseController.h"

class ObjectsGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) override;
};

#endif // !__ObjectsGETController_H__