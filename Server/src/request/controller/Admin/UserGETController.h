#ifndef __UserGETController_H__
#define __UserGETController_H__

#include "../IBaseController.h"

class UserGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) override;
};

#endif // !__UserGETController_H__