#include <stdafx.h>
#include "appInstance.h"

#include "../db/log/DatabaseLogger.h"
#include <Poco/File.h>
#include <Poco/Exception.h>

//#include <Poco/SQL/PostgreSQL/Connector.h>

appInstance *appInstance::get()
{
    static appInstance *instance = nullptr;
    if (!instance)
        instance = new appInstance;
    return instance;
}

bool appInstance::Initialize()
{
    // Poco::SQL::PostgreSQL::Connector::registerConnector();

    _CurrentPath = Poco::Path("./");
    _CurrentPath = _CurrentPath.absolute();
    _DbPath._Current = _CurrentPath;
    _DbPath._Current.append(Poco::Path("Database"));
    _DbPath._Master = _DbPath._Current;
    _DbPath._Master.append(Poco::Path("Master"));
    _DbPath._Options = _DbPath._Current;
    _DbPath._Options.append(Poco::Path("Options"));

    printf("Current directory = %s\n", _CurrentPath.toString().c_str());
    printf("Databese [master] directory = %s\n", _DbPath._Master.toString().c_str());
    printf("Databese [options] directory = %s\n", _DbPath._Options.toString().c_str());


    Poco::File dataPath(_DbPath._Current);
    dataPath.createDirectory();

    Poco::File optionsPath(_DbPath._Options);
    optionsPath.createDirectory();

    Poco::File masterPath(_DbPath._Master);
    masterPath.createDirectory();

    _Options.reset(new OptionsModel);
    if (!_Options->Initialize(_DbPath._Options.toString()))
    {
        printf("Error: Database/Options::Initialize\n");
        return false;
    }

    _Master.reset(new ListModel);
    if (!_Master->Initialize(_DbPath._Master.toString()))
    {
        printf("Error: Database/Master::Initialize\n");
        return false;
    }

    return true;
}

void appInstance::Shutdown()
{
}

void appInstance::Process()
{
}