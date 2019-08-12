#ifndef __ObjectsPOSTController_H__
#define __ObjectsPOSTController_H__

#include "../../IBaseController.h"

class ObjectsPOSTController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) override;
};

#endif // !__ObjectsPOSTController_H__