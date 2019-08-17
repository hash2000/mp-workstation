#ifndef __ObjectsGetController_H__
#define __ObjectsGetController_H__

#include "../../IBaseController.h"

class ObjectsGetController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) override;
};

#endif // !__ObjectsGetController_H__