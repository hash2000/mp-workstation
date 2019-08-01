#ifndef __IBASECONTROLLER_H__
#define __IBASECONTROLLER_H__

#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Query.h>
#include <Poco/JSON/JSONException.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/JSON/ParseHandler.h>
#include <Poco/JSON/PrintHandler.h>
#include <Poco/JSON/Template.h>

class DatabaseManager;

class IBaseController
{
public:
    virtual Poco::JSON::Object::Ptr HandleRequest(DatabaseManager* dbManager,
        Poco::JSON::Object::Ptr arguments) = 0;
};


#endif // !__IBASECONTROLLER_H__