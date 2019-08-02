#ifndef __USERCONTROLLER_H__
#define __USERCONTROLLER_H__

#include "../interface/IBaseController.h"

class UserController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments) override;
};

#endif // !__USERCONTROLLER_H__