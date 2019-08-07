#ifndef __DatabaseManager_H__
#define __DatabaseManager_H__

#include "../model/system/SystemObjectsModel.h"

class DatabaseManager
{
public:
    void Initialize();

public:
    SystemObjectsModel _SystemObjectsModel;
};

#endif // !__DatabaseManager_H__
