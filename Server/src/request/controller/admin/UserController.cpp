#include <stdafx.h>
#include "UserController.h"

Poco::JSON::Object::Ptr UserController::HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();
    json->set("total", 0);
    json->set("success", true);    
    //json->set("items", nullptr);

    return json;
}
