#ifndef __SystemObjectsModel_H__
#define __SystemObjectsModel_H__

#include "../ModelWrapper.h"
#include "../IncrementIdentity.h"
#include "SystemObjects.h"



class SystemObjectsModel : public ModelWrapper
{
public:
    bool Initialize(const std::string &path,
        leveldb::Comparator * comparator = nullptr) override;

    //void Add()

    //std::shared_ptr<leveldb::Iterator> GetItem(int id);

private:
    IncrementIdentity _Identity;
};


#endif // !__SystemObjectsModel_H__