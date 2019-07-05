#ifndef __WORKCONTEXT_H__
#define __WORKCONTEXT_H__


#include "../../controller/BaseController.h"
#include "../../layout/LayoutBuilder.h"

#include <Poco/Path.h>

#include <functional>
#include <string>



class WorkContext
{
public:
    std::string _ContentType;
    Poco::Path _Path;
    LayoutBuilder * _Layout;
};


#endif // !__WORKCONTEXT_H__