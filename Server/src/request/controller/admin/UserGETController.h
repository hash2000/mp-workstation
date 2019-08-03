#ifndef __USERGETCONTROLLER_H__
#define __USERGETCONTROLLER_H__

#include "../interface/IBaseController.h"

class UserGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments) override;
};

#endif // !__USERGETCONTROLLER_H__