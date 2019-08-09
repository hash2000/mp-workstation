#ifndef __IBaseController_H__
#define __IBaseController_H__

#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Query.h>
#include <Poco/JSON/JSONException.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/JSON/ParseHandler.h>
#include <Poco/JSON/PrintHandler.h>
#include <Poco/JSON/Template.h>
#include <Poco/Dynamic/Var.h>

class DatabaseManager;

class IBaseController
{
public:
    virtual Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* db,
        Poco::Dynamic::Var arguments) = 0;
};


#endif // !__IBaseController_H__