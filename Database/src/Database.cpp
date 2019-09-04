#include <stdafx.h>
#include <Poco/Path.h>

#include "Database.h"


class DatabaseImpl : public Database
{
public:
    DatabaseImpl(
        const std::string & path,
        const std::string & name)
        : _InitPath(path)
        , _Name(name)
    {
    }

    bool Initialize()
    {
        _BasePath = _InitPath;
        _BasePath.append(_Name);
        _DataPath = _BasePath;
        _DataPath.append("Data");
        _IndexesPath = _BasePath;
        _IndexesPath.append("Indexes");
        return true;
    }

public:
    std::string _Name;
    Poco::Path _InitPath;
    Poco::Path _BasePath;
    Poco::Path _DataPath;
    Poco::Path _IndexesPath;
};





std::shared_ptr<Database> Database::Create(
        const std::string & path,
        const std::string & name)
{
    return std::make_shared<DatabaseImpl>(path, name);
}