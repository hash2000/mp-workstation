#ifndef __SystemObjectsComparator_H__
#define __SystemObjectsComparator_H__

#include <leveldb/db.h>
#include <leveldb/cache.h>
#include <leveldb/comparator.h>

#include "SystemObjects.h"

class SystemObjectsComparator: public leveldb::Comparator
{
public:
    int Compare(
        const leveldb::Slice& a, 
        const leveldb::Slice& b) const;

    const char* Name() const;

    void FindShortestSeparator(
        std::string*, const leveldb::Slice&) const;

    void FindShortSuccessor(
        std::string*) const;
};


#endif // !__SystemObjectsComparator_H__