#ifndef __RouteMap_H__
#define __RouteMap_H__

#include <Poco/Mutex.h>
#include <Poco/URI.h>
#include <Poco/Util/PropertyFileConfiguration.h>

#include <string>
#include <map>

#include "context/WorkContext.h"
#include "../layout/LayoutTemplate.h"
#include "../controller/IBaseController.h"

class RouteMap
{
    friend class WorkContextScope;
public:

    void Initialize();

    WorkContext * GetWorkContext(
        const Poco::URI & uri, 
        const std::string & method);     

    void RegisterRoute(
        const std::string & path, 
        const std::string & method, 
        IBaseController * controller);

private:
    void RegisterRouteUnsafe(
        const std::string & path, 
        const std::string & method, 
        IBaseController * controller);


private:
    Poco::Mutex _RoutesLock;
    LayoutTemplate _LayoutTemplates;
    std::map<std::string, WorkContext*> _Routes;
    Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> _MimeTypes;
    std::string _DefaultRoute;
};

#endif // !__RouteMap_H__
