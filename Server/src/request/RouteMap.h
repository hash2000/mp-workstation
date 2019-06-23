#ifndef __ROUTEMAP_H__
#define __ROUTEMAP_H__

#include <string>
#include <map>

#include "WorkContext.h"


class RouteMap
{
public:
    void Initialize();
    const WorkContext * GetWorkContext(
        const std::string & uri, const std::string & method) const;     

private:
    void RegisterRoute(
        const std::string & uri, const std::string & method);

private:
    std::map<std::string, WorkContext*> _Routes;
};

#endif // !__ROUTEMAP_H__
