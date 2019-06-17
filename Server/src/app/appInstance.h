#ifndef __APPINSTANCE_H__
#define __APPINSTANCE_H__

#include <Poco/Path.h>
#include "../db/model/ListModel.h"
#include "../db/model/OptionsModel.h"


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
    std::shared_ptr<ListModel> _Master;
    std::shared_ptr<OptionsModel> _Options;
};

#endif // !__APPINSTANCE_H__
