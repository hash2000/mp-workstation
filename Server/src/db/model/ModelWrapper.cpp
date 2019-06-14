#include <stdafx.h>
#include "ModelWrapper.h"

bool ModelWrapper::Initialize(const std::string &path)
{
    leveldb::Options opt;
    opt.create_if_missing = true;
    opt.compression = leveldb::kNoCompression;

    leveldb::DB *initStore;
    leveldb::Status status = leveldb::DB::Open(opt, path, &initStore);
    if (!status.ok())
    {

        return false;
    }

    _store.reset(initStore);

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

bool ModelWrapper::Add()
{

    return true;
}