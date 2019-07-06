#ifndef __ROUTEMAP_H__
#define __ROUTEMAP_H__

#include <Poco/Mutex.h>

#include <string>
#include <map>

#include "context/WorkContext.h"


class RouteMap
{
    friend class WorkContextScope;
public:

    void Initialize();

    WorkContext * GetWorkContext(
        const std::string & uri, 
        const std::string & method);     

private:
    void InitializeContentTypes();

private:
    Poco::Mutex _RoutesLock;
    std::map<std::string, WorkContext*> _Routes;
    std::map<std::string, std::string> _ContentTypesByExtensions;
    std::string _DefaultRoute;
};

#endif // !__ROUTEMAP_H__
