#include <stdafx.h>
#include "LayoutBuilder.h"
#include "LayoutTemplate.h"
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
    
    if (layout.empty())
        throw Poco::NotFoundException("LayoutBuilder::Initialize [//partialView:layout] attribute not found");
    auto layoutDocument = layouts->GetTemplate(layout);
    if (!layoutDocument)
        throw Poco::Exception("LayoutBuilder::Initialize layout with name [" + layout + "] not found");
    
    auto layoutHead = _Document->importNode(layoutDocument->getNodeByPath("//layout/head"), true);
    if (layoutHead) {
        // Poco::XML::TreeWalker walker(layoutHead, Poco::XML::NodeFilter::SHOW_ELEMENT);
		// auto node = walker.currentNode();
        // while(node) {
        //     _Head->appendChild(node);
        //     node = walker.nextNode();
        // }
        Poco::AutoPtr<Poco::XML::NodeList> layoutHeadList = layoutHead->childNodes();
        for (unsigned long i = 0, __end = layoutHeadList->length(); i < __end; i++) {
            auto node = layoutHeadList->item(i);
            if (node && node->nodeType() == Poco::XML::Node::ELEMENT_NODE)
                _Head->appendChild(node);
        }
    }

    if (!title.empty()) {
        auto titleElement = _Document->createElement("title");
        auto titleElementText = _Document->createTextNode(title);
        titleElement->appendChild(titleElementText);
        _Head->appendChild(titleElement);
    }

    auto layoutBody = _Document->importNode(layoutDocument->getNodeByPath("//layout/body"), true);
    if (layoutBody) {
        // Poco::XML::TreeWalker walker(layoutBody, Poco::XML::NodeFilter::SHOW_ELEMENT);
		// auto node = walker.currentNode();
        // while(node) {
        //     auto t = static_cast<Poco::XML::Element*>(node)->nodeName();
        //     _Body->appendChild(node);
        //     node = walker.nextNode();
        // }
        Poco::AutoPtr<Poco::XML::NodeList> layoutBodyList = layoutBody->childNodes();
        for (unsigned long i = 0, __end = layoutBodyList->length(); i < __end; i++) {
            auto node = layoutBodyList->item(i);
            if (node && node->nodeType() == Poco::XML::Node::ELEMENT_NODE)
                _Body->appendChild(node);
        }
    }

    Poco::AutoPtr<Poco::XML::NodeList> partialViewNodeList = partialViewNode->childNodes();
    for (unsigned long i = 0, __end = partialViewNodeList->length(); i < __end; i++) {
        auto node = partialViewNodeList->item(i);
        if (node && node->nodeType() == Poco::XML::Node::ELEMENT_NODE)
            _Body->appendChild(node);
    }
}

