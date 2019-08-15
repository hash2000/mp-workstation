#ifndef __ObjectTypesGETController_H__
#define __ObjectTypesGETController_H__

#include "../../IBaseController.h"

class ObjectTypesGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) override;
private:
    Poco::JSON::Array::Ptr _Items = new Poco::JSON::Array();
};

#endif // !__ObjectTypesGETController_H__