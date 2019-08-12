#include <stdafx.h>
#include "ObjectsPOSTController.h"

#include "../../../../db/manager/DatabaseManager.h"
#include "../../../../db/model/system/SystemObjects.h"

#include <Poco/Dynamic/Struct.h>

#include <list>

Poco::JSON::Object::Ptr ObjectsPOSTController::HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();

    if (arguments.type() != typeid(Poco::JSON::Object))
        return json;
    
    auto argumentsObject = arguments
        .extract<Poco::JSON::Object>();

    

    return json;
}
