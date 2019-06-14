#ifndef __MODELWRAPPER_H__
#define __MODELWRAPPER_H__

#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <leveldb/table.h>

#include <memory>
#include <string>
#include <atomic>

class ModelWrapper
{
public:
    bool Initialize(const std::string & path);
    bool Add();
private:
    std::shared_ptr<leveldb::Cache> _cache;
    std::shared_ptr<leveldb::DB> _store;
    std::atomic<std::size_t> _identity;
};


#endif
