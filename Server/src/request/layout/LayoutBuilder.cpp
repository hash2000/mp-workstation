#include <stdafx.h>
#include "LayoutBuilder.h"
#include "LayoutTemplate.h"
#include "../route/context/WorkContext.h"

#include <Poco/UnicodeConverter.h>

void LayoutBuilder::Initialize(WorkContext * context, const LayoutTemplate* layouts)
{
    ResetDocument();

    Poco::XML::InputSource source(context->_Path.toString());    
    source.setEncoding("UTF8");
    Poco::XML::DOMParser parser;
    DocPtr partialViewDocument = parser.parse(&source);

    auto partialViewNode = partialViewDocument->getNodeByPath("//partialView");
    if (!partialViewNode)
        throw Poco::NotFoundException("LayoutBuilder::Initialize [//partialView] not found");
    partialViewNode = _Document->importNode(partialViewNode, true);
    auto title = static_cast<Poco::XML::Element*>(partialViewNode)->getAttribute("title");
    auto layout = static_cast<Poco::XML::Element*>(partialViewNode)->getAttribute("layout");
    
    if (layout.empty())
        throw Poco::NotFoundException("LayoutBuilder::Initialize [//partialView:layout] attribute not found");
    auto layoutDocument = layouts->GetTemplate(layout);
    if (!layoutDocument)
        throw Poco::Exception("LayoutBuilder::Initialize layout with name [" + layout + "] not found");
    
    auto layoutHead = _Document->importNode(layoutDocument->getNodeByPath("//layout/head"), true);
    if (layoutHead) {
        Poco::XML::TreeWalker walker(layoutHead, Poco::XML::NodeFilter::SHOW_ELEMENT);
		Poco::XML::Node* node = walker.currentNode();
        while(node) {
            _Head->appendChild(node);
            node = walker.nextNode();
        }
    }

    if (!title.empty()) {
        std::string convTitle;
        Poco::UnicodeConverter::convert(title, convTitle);
        auto titleElement = _Document->createElement("title");
        auto titleElementText = _Document->createTextNode(convTitle);
        titleElement->appendChild(titleElementText);
        _Head->appendChild(titleElement);
    }

    auto layoutBody = _Document->importNode(layoutDocument->getNodeByPath("//layout/body"), true);
    if (layoutBody) {
        Poco::XML::TreeWalker walker(layoutBody, Poco::XML::NodeFilter::SHOW_ELEMENT);
		Poco::XML::Node* node = walker.currentNode();
        while(node) {
            _Body->appendChild(node);
            node = walker.nextNode();
        }
    }

}

