#include <stdafx.h>
#include "DatabaseManager.h"

#include "../model/system/SystemObjectsComparator.h"

void DatabaseManager::Initialize()
{
    _SystemObjectsModel.Initialize("Data/Stores/System/Objects",
        new SystemObjectsComparator);
}
