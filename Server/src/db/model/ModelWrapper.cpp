#include <stdafx.h>
#include "ModelWrapper.h"

ModelWrapper::~ModelWrapper()
{
}

bool ModelWrapper::Initialize(const std::string &path,
        leveldb::Comparator * comparator)
{
    auto & app = Poco::Util::Application::instance();
    
    leveldb::Options opt;
    opt.create_if_missing = true;
    //opt.error_if_exists = true;
    //opt.compression = leveldb::kNoCompression;

    if (comparator) {
        opt.comparator = comparator;
        _comparator = std::shared_ptr<leveldb::Comparator>(
            comparator);
    }

    leveldb::DB *initStore;
    leveldb::Status status = leveldb::DB::Open(opt, path, &initStore);
    if (!status.ok())
    {
        app.logger().error("ModelWrapper::Initialize from path " + 
            path + " status " + status.ToString());
        return false;
    }

    _store.reset(initStore);

    app.logger().information("ModelWrapper::Initialize from path " + 
        path);

    return true;
}

void ModelWrapper::Shutdown()
{
    _store.reset();
}