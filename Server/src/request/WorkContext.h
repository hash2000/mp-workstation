#ifndef __WORKCONTEXT_H__
#define __WORKCONTEXT_H__


#include "layout/LayoutBuilder.h"
#include "controller/BaseController.h"
#include <functional>
#include <string>

class WorkContext
{
public:
    typedef std::function<BaseController*(WorkContext*)> 
        ControllerFactoryHandler;

public:
    std::string _Controller;
    std::string _Action;
    std::string _Method;
    LayoutBuilder * _Layout;
    ControllerFactoryHandler _ControllerFactory;
};


#endif // !__WORKCONTEXT_H__