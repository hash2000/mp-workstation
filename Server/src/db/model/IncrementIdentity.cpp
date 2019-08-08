#include <stdafx.h>
#include "IncrementIdentity.h"

bool IncrementIdentity::ReloadIdentities(std::shared_ptr<leveldb::DB> store)
{
    std::unique_ptr<leveldb::Iterator> it(
        store->NewIterator(leveldb::ReadOptions()));
        
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        auto slice = it->key();
        auto id = reinterpret_cast<const std::size_t *>(slice.data());
        if (_identity.load(std::memory_order_relaxed) < *id)
            _identity = *id;
    }

    return true;
}

std::size_t IncrementIdentity::NewIdentity() {
    return _identity.fetch_add(1);
}