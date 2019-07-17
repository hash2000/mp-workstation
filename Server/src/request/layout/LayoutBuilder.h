#ifndef __LAYOUTBUILDER_H__
#define __LAYOUTBUILDER_H__

#include "html/HtmlLayout.h"

class WorkContext;
class LayoutTemplate;

class LayoutBuilder : public HtmlLayout
{

public:
    void Initialize(WorkContext * context, const LayoutTemplate* layouts);

};



#endif // !__LAYOUTBUILDER_H__