#include <stdafx.h>
#include "DatabaseGETController.h"

Poco::JSON::Object::Ptr DatabaseGETController::HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();
    json->set("total", 0);
    json->set("success", true);    
    //json->set("items", nullptr);

    return json;
}
