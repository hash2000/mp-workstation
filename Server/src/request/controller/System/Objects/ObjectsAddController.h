#ifndef __ObjectsAddController_H__
#define __ObjectsAddController_H__

#include "../../IBaseController.h"

class ObjectsAddController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) override;
};

#endif // !__ObjectsAddController_H__