#ifndef __MODELWRAPPER_H__
#define __MODELWRAPPER_H__

#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <leveldb/table.h>

#include <memory>
#include <string>

class ModelWrapper
{
public:
    virtual bool Initialize(const std::string &path);
    virtual void Shutdown();

protected:
    std::shared_ptr<leveldb::Cache> _cache;
    std::shared_ptr<leveldb::DB> _store;
};

#endif
