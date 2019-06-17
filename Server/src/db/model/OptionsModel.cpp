#include <stdafx.h>
#include "OptionsModel.h"

bool OptionsModel::Set(const std::string &name, const std::string &value)
{
    leveldb::Slice key(name);
    leveldb::Slice val(value);

    auto status = _store->Put(leveldb::WriteOptions(), key, val);
    if (!status.ok())
    {
        printf("Error set  parameter %s\n", name.c_str());
    }
    return status.ok();
}

std::string OptionsModel::GetString(const std::string &name) const
{
    std::string value;
    leveldb::Slice key(name);

    auto status = _store->Get(leveldb::ReadOptions(), key, &value);
    if (!status.ok())
    {
        return std::string();
    }
    return value;
}

bool OptionsModel::GetBoolean(const std::string &name) const
{
    auto result = GetString(name);
    return result == "true";
}

int OptionsModel::GetInteger(const std::string &name, int defaultValue) const
{
    auto result = GetString(name);
    if (result.empty())
        return defaultValue;
    return std::atoi(result.c_str());
}

double OptionsModel::GetDouble(const std::string &name, double defaultValue) const
{
    auto result = GetString(name);
    if (result.empty())
        return defaultValue;
    return std::atof(result.c_str());
}
