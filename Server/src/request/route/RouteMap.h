#ifndef __ROUTEMAP_H__
#define __ROUTEMAP_H__

#include <Poco/Mutex.h>

#include <string>
#include <map>

#include "context/WorkContext.h"


class RouteMap
{
public:
    static const std::string DefaultArea;
    static const std::string DefaultController;
    static const std::string DefaultAction;
    static const std::string DefaultActionExtension;


    void Initialize();
    
    WorkContext * GetWorkContext(
        const std::string & uri, 
        const std::string & method);     

private:
    WorkContext * GetContentWorkContext(
        const std::string & uri, 
        const std::string & method);
    WorkContext * GetAreaViewWorkContext(
        const std::string & uri, 
        const std::string & method);


private:
    Poco::Mutex _RoutesLock;
    std::map<std::string, WorkContext*> _ContentRoutes;
    std::map<std::string, WorkContext*> _AreaViewRoutes;
};

#endif // !__ROUTEMAP_H__
