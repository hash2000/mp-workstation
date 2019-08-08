#include <stdafx.h>
#include "SystemObjectsComparator.h"

int SystemObjectsComparator::Compare(
    const leveldb::Slice& a,
    const leveldb::Slice& b) const
{
    const auto left = reinterpret_cast<const SystemObject*>(a.data());
    const auto right = reinterpret_cast<const SystemObject*>(b.data());
    if (left->Id < right->Id)
        return -1;
    if (left->Id > right->Id)
        return 1;        
    return 0;
}

const char* SystemObjectsComparator::Name() const {
    return "SystemObjectsComparator";
}
void SystemObjectsComparator::FindShortestSeparator(
    std::string*, const leveldb::Slice&) const {
}
void SystemObjectsComparator::FindShortSuccessor(
    std::string*) const {
}
