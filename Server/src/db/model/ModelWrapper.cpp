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

    return true;
}

void ModelWrapper::Shutdown()
{
    _store.reset();
}