#ifndef __DATABASEGETCONTROLLER_H__
#define __DATABASEGETCONTROLLER_H__

#include "../interface/IBaseController.h"

class DatabaseGETController : public IBaseController
{
public:
    Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments) override;
};

#endif // !__DATABASEGETCONTROLLER_H__