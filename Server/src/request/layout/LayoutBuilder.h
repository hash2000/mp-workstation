#ifndef __LayoutBuilder_H__
#define __LayoutBuilder_H__

#include "html/HtmlLayout.h"

class WorkContext;
class LayoutTemplate;

class LayoutBuilder : public HtmlLayout
{

public:
    void Initialize(WorkContext * context, const LayoutTemplate* layouts);

};



#endif // !__LayoutBuilder_H__