#include <stdafx.h>
#include "ObjectTypesGETController.h"

#include "../../../../db/manager/DatabaseManager.h"
#include "../../../../db/model/system/SystemObjects.h"

#include <Poco/Dynamic/Struct.h>

#include <list>

Poco::JSON::Object::Ptr ObjectTypesGETController::HandleRequest(DatabaseManager* db,
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

    if (_Items->size() == 0) {
        _Items->add(Poco::DynamicStruct( {
                { "id", SystemObjectType::Directory },
                { "Name", "Directory" }
            })
        );
        _Items->add(Poco::DynamicStruct( {
                { "id", SystemObjectType::Dimension },
                { "Name", "Dimension" }
            })
        );
        _Items->add(Poco::DynamicStruct( {
                { "id", SystemObjectType::DimensionAttribute },
                { "Name", "DimensionAttribute" }
            })
        );
    }

    json->set("items", _Items);

    return json;
}
