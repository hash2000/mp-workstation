#ifndef __ModelWrapper_H__
#define __ModelWrapper_H__

#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <leveldb/table.h>

#include <memory>
#include <string>

class ModelWrapper
{
public:
    virtual ~ModelWrapper();
    virtual bool Initialize(const std::string &path);
    virtual void Shutdown();

protected:
    std::shared_ptr<leveldb::DB> _store;
};

#endif // !__ModelWrapper_H__
