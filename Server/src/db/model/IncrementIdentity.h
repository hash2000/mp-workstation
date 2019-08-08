#ifndef __IncrementIdentity_H__
#define __IncrementIdentity_H__

#include <leveldb/db.h>
#include <atomic>
#include <memory>

class IncrementIdentity
{
public:
    bool ReloadIdentities(std::shared_ptr<leveldb::DB> store);
    std::size_t NewIdentity();

protected:
    std::atomic<std::size_t> _identity;
};

#endif // !__IncrementIdentity_H__
