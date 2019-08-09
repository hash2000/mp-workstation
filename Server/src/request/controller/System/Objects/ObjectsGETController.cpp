#include <stdafx.h>
#include "ObjectsGETController.h"

Poco::JSON::Object::Ptr ObjectsGETController::HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();
    json->set("total", 0);
    json->set("success", true);    
    //json->set("items", nullptr);

    

    return json;
}
