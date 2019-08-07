#ifndef __DATABASEMANAGER_H__
#define __DATABASEMANAGER_H__

#include "../model/system/SystemObjectsModel.h"

class DatabaseManager
{
public:
    void Initialize();

public:
    SystemObjectsModel _SystemObjectsModel;
};

#endif // !__DATABASEMANAGER_H__
