#include <stdafx.h>
#include "OptionsModel.h"


bool OptionsModel::Set(const std::string & name, const std::string & value)
{
    leveldb::Slice key(name);
    leveldb::Slice val(value);

    auto status = _store->Put(leveldb::WriteOptions(), key, val);
    if(!status.ok()) {
        printf("Error set  parameter %s\n", name.c_str());
    }
    return status.ok();
}

std::string OptionsModel::GetString(const std::string & name) const
{
    return std::string();
}

bool OptionsModel::GetBoolean(const std::string & name) const
{
    return true;
}

int OptionsModel::GetInteger(const std::string & name) const
{
    return 0;
}

double OptionsModel::GetDouble(const std::string & name) const
{
    return 0.;
}
