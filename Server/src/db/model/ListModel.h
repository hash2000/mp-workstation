#ifndef __ListModel_H__
#define __ListModel_H__

#include "ModelWrapper.h"

#include <atomic>

class ListModel : public ModelWrapper
{
public:
    virtual ~ListModel() {
    }  
    
    virtual bool Initialize(const std::string &path) override;

protected:
    std::atomic<std::size_t> _identity;
};

#endif // !__ListModel_H__
