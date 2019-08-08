#include <stdafx.h>
#include "SystemObjectsModel.h"


bool SystemObjectsModel::Initialize(const std::string &path,
        leveldb::Comparator * comparator)
{
    if (!ModelWrapper::Initialize(path, comparator))
        return false;

    if (!_Identity.ReloadIdentities(_store))
        return false;

    return true;
}

