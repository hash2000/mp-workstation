#include <stdafx.h>
#include "Server.h"

#include "app/appInstance.h"

int main()
{
    auto instance = appInstance::get();
    if (!instance->Initialize())
        return 1L;
    instance->Process();
    instance->Shutdown();

    return 0L;
}