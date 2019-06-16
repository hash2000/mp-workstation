#ifndef __APPINSTANCE_H__
#define __APPINSTANCE_H__

#include <Poco/Path.h>
#include "../db/model/ListModel.h"


class appInstance
{
public:
    static appInstance * get();

public:
    bool Initialize();
    void Shutdown();
    void Process();

public:
    Poco::Path _CurrentPath;
    
    struct {
        Poco::Path _Current;
        Poco::Path _Master;
        Poco::Path _Options;
    } _DbPath;

private:
    ListModel * _MasterData;
};

#endif // !__APPINSTANCE_H__
