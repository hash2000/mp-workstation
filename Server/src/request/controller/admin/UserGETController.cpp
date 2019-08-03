#include <stdafx.h>
#include "UserGETController.h"

Poco::JSON::Object::Ptr UserGETController::HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();
    json->set("total", 0);
    json->set("success", true);    
    //json->set("items", nullptr);

    return json;
}
