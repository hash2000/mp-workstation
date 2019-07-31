#ifndef __ROUTEMAP_H__
#define __ROUTEMAP_H__

#include <Poco/Mutex.h>
#include <Poco/Util/PropertyFileConfiguration.h>

#include <string>
#include <map>

#include "context/WorkContext.h"
#include "../layout/LayoutTemplate.h"


class RouteMap
{
    friend class WorkContextScope;
public:

    void Initialize();

    WorkContext * GetWorkContext(
        const std::string & uri, 
        const std::string & method);     

private:
    Poco::Mutex _RoutesLock;
    LayoutTemplate _LayoutTemplates;
    std::map<std::string, WorkContext*> _Routes;
    Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> _MimeTypes;
    std::string _DefaultRoute;
};

#endif // !__ROUTEMAP_H__
