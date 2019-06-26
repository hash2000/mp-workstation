#ifndef __ROUTEMAP_H__
#define __ROUTEMAP_H__

#include <string>
#include <map>

#include "context/WorkContext.h"


class RouteMap
{
public:
    void Initialize();
    WorkContext * GetWorkContext(
        const std::string & uri, 
        const std::string & method) const;     

private:
    void RegisterRoute(
        const std::string & controller,
        const std::string & action,
        const std::string & method,
        WorkContext::ControllerFactoryHandler handler);

private:
    std::map<std::string, WorkContext*> _Routes;
};

#endif // !__ROUTEMAP_H__
