#include <stdafx.h>
#include "LayoutBuilder.h"
#include "../route/context/WorkContext.h"

void LayoutBuilder::Initialize(WorkContext * context, const LayoutTemplate* layouts)
{
    ResetDocument();

    Poco::XML::InputSource source(context->_Path.toString());    
    Poco::XML::DOMParser parser;
    DocPtr partialViewDocument = parser.parse(&source);

    auto partialViewNode = partialViewDocument->getNodeByPath("//partialView");
    if (!partialViewNode)
        throw Poco::NotFoundException("LayoutBuilder::Initialize [//partialView] not found");
    partialViewNode = _Document->importNode(partialViewNode, true);
    auto title = static_cast<Poco::XML::Element*>(partialViewNode)->getAttribute("title");
    auto layout = static_cast<Poco::XML::Element*>(partialViewNode)->getAttribute("layout");
}

