#ifndef __ObjectTypesGetController_H__
#define __ObjectTypesGetController_H__

#include "../../IBaseController.h"

class ObjectTypesGetController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) override;
private:
    Poco::JSON::Array::Ptr _Items = new Poco::JSON::Array();
};

#endif // !__ObjectTypesGetController_H__