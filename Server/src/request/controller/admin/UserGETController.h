#ifndef __UserGETController_H__
#define __UserGETController_H__

#include "../interface/IBaseController.h"

class UserGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments) override;
};

#endif // !__UserGETController_H__