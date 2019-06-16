#include <stdafx.h>
#include "ModelWrapper.h"

ModelWrapper::~ModelWrapper()
{
}

bool ModelWrapper::Initialize(const std::string &path)
{
    leveldb::Options opt;
    opt.create_if_missing = true;
    //opt.error_if_exists = true;
    //opt.compression = leveldb::kNoCompression;

    leveldb::DB *initStore;
    leveldb::Status status = leveldb::DB::Open(opt, path, &initStore);
    if (!status.ok())
    {
        printf("Error ModelWrapper::Initialize: %s\n", status.ToString().c_str());
        return false;
    }

    _store.reset(initStore);

    return true;
}

void ModelWrapper::Shutdown()
{
    _store.reset();
}