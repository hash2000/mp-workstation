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

    json->set("total", 1);
    json->set("success", true); 

    Poco::DynamicStruct model = *item.extract<Poco::JSON::Object::Ptr>();
    SystemObject itemValue;

    itemValue.ParentId = 0;
    itemValue.Type = SystemObjectType::Directory;

    auto parentIdvar = model["parentId"];
    if (parentIdvar.isInteger()) {
        itemValue.ParentId = parentIdvar.convert<std::size_t>();
    }

    auto typeIdvar = model["TypeId"];
    if (typeIdvar.isInteger()) {
        itemValue.Type = (SystemObjectType)typeIdvar.convert<int>();
    }    

    auto namevar = model["Name"];
    if (namevar.isString()) {
        itemValue.Name = namevar.convert<std::string>();
    } 

    auto result = db->_SystemObjectsModel.Add(
        itemValue.ParentId,
        itemValue.Type,
        itemValue.Name
    );

    Poco::DynamicStruct ds;
    ds["id"] = result->Id;
    ds["parentId"] = result->ParentId;
    ds["Name"] = result->Name;
    ds["TypeId"] = result->Type;
    ds["TypeName"] = result->TypeName;
    ds["ModifiedDate"] = result->ModifiedDate;

    json->set("items", ds);

    return json;
}
