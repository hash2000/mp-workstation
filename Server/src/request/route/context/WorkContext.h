#ifndef __WORKCONTEXT_H__
#define __WORKCONTEXT_H__

#include "../../layout/LayoutBuilder.h"

#include <Poco/Path.h>
#include <Poco/LocalDateTime.h>

#include <functional>
#include <string>



class WorkContext
{
public:
    LayoutBuilder * _Layout;
    std::string _ContentType;
    Poco::Path _Path;
    Poco::LocalDateTime _PathReadTime;
};


#endif // !__WORKCONTEXT_H__