#include <stdafx.h>
#include "ObjectTypesGetController.h"

#include "../../../../db/manager/DatabaseManager.h"
#include "../../../../db/model/system/SystemObjects.h"

#include <Poco/Dynamic/Struct.h>

#include <list>

Poco::JSON::Object::Ptr ObjectTypesGetController::HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments)
{
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object();

    if (arguments.type() != typeid(Poco::JSON::Object::Ptr))
        return json;
    
    json->set("total", 0);
    json->set("success", true);    

    if (_Items->size() == 0) {
        _Items->add(Poco::DynamicStruct( {
                { "Id", (int)SystemObjectType::Directory },
                { "Name", "Directory" }
            })
        );
        _Items->add(Poco::DynamicStruct( {
                { "Id", (int)SystemObjectType::Dimension },
                { "Name", "Dimension" }
            })
        );
        _Items->add(Poco::DynamicStruct( {
                { "Id", (int)SystemObjectType::DimensionAttribute },
                { "Name", "DimensionAttribute" }
            })
        );
    }

    json->set("items", _Items);
    json->set("total", _Items->size());

    return json;
}
