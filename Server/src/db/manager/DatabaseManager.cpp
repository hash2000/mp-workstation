#include <stdafx.h>
#include "DatabaseManager.h"


void DatabaseManager::Initialize()
{
    _SystemObjectsModel.Initialize("Data/Stores/System/Objects");
}
