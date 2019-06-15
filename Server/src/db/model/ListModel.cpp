#include <stdafx.h>
#include "ListModel.h"

bool ListModel::Initialize(const std::string &path)
{
    if (!ModelWrapper::Initialize(path))
        return false;

    std::unique_ptr<leveldb::Iterator> it(
        _store->NewIterator(leveldb::ReadOptions()));
        
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        auto slice = it->key();
        auto id = reinterpret_cast<const std::size_t *>(slice.data());
        if (_identity.load(std::memory_order_relaxed) < *id)
            _identity = *id;
    }

    return true;
}