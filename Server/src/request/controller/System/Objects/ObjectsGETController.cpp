#include <stdafx.h>
#include "ObjectsGETController.h"

#include "../../../../db/manager/DatabaseManager.h"
#include "../../../../db/model/system/SystemObjects.h"

#include <Poco/Dynamic/Struct.h>

#include <list>

Poco::JSON::Object::Ptr ObjectsGETController::HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();

    if (arguments.type() != typeid(Poco::JSON::Object::Ptr))
        return json;
    
    auto argumentsObject = arguments
        .extract<Poco::JSON::Object::Ptr>();
    if (argumentsObject.isNull())
        return json;

    std::size_t id = 0;
    if (!argumentsObject->isNull("node")) {
        auto idVar = argumentsObject->get("node");
        if (!idVar.isEmpty() && idVar.type() == typeid(std::size_t)) {           
            id = idVar;
        }
    }

    json->set("total", 0);
    json->set("success", true);    

    std::list<std::shared_ptr<SystemObject>> children;
    db->_SystemObjectsModel.GetNode(children, id);

    Poco::JSON::Array::Ptr items = new Poco::JSON::Array();
    for (auto begin = children.begin(), end = children.end(); 
        begin != end; begin ++) 
    {
        auto model = *begin;

        Poco::DynamicStruct ds;
        ds["id"] = model->Id;
        ds["parentId"] = model->ParentId;
        ds["Name"] = model->Name;
        ds["TypeId"] = model->Type;
        ds["TypeName"] = model->TypeName;
        ds["ModifiedDate"] = model->ModifiedDate;

        items->add(ds);
    }

    json->set("items", items);

    return json;
}
