#include <stdafx.h>
#include "ObjectsAddController.h"

#include "../../../../db/manager/DatabaseManager.h"
#include "../../../../db/model/system/SystemObjects.h"

#include <Poco/Dynamic/Struct.h>

#include <list>

Poco::JSON::Object::Ptr ObjectsAddController::HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();
    if (arguments.type() != typeid(Poco::JSON::Object::Ptr))
        return json;

    auto argumentsObject = arguments
        .extract<Poco::JSON::Object::Ptr>();
    if (argumentsObject.isNull())
        return json;

    auto item = argumentsObject->get("item");
    if (item.isEmpty())
        return json;

    Poco::DynamicStruct model = *item.extract<Poco::JSON::Object::Ptr>();

    // db->_SystemObjectsModel.Add(
    //     model["parentId"].extract<std::size_t>());
    

    return json;
}
