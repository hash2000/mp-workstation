#include <stdafx.h>

#include <Poco/SAX/InputSource.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/Exception.h>

#include "LayoutBuilder.h"
#include "../route/context/WorkContext.h"

void LayoutBuilder::Initialize(WorkContext * context)
{
    if (_Document)
        _Document->release();

    _Document = new Poco::XML::Document;
    _Html = _Document->createElement("html");
    _Head = _Document->createElement("head");
    _Body = _Document->createElement("body");

    AddTag("meta", AttributeList {
        { "http-equiv", "X-UA-Compatible" },
        { "content", "IE=edge" },
    });

    AddTag("meta", AttributeList {
        { "name", "viewport" },
        { "content", "width=device-width, initial-scale=1, maximum-scale=10, user-scalable=yes" },
    });

    _Document->appendChild(_Html);
    _Html->appendChild(_Head);
    _Html->appendChild(_Body);

    AddViewContent(context);

}

void LayoutBuilder::AddViewContent(WorkContext * context)
{
    Poco::XML::InputSource source(context->_RelativePath);    
    
    try{
        Poco::XML::DOMParser parser;
        // parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, false);
	    // parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACE_PREFIXES, false);
		Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&source);
	
        auto clonedNode = _Document->importNode(pDoc->documentElement(), true);   
        auto partialViewNode = clonedNode->getNodeByPath("/partialView");
        if (!partialViewNode) {
            printf("Error LayoutBuilder::AddViewContent partialView nodes not found\n");
            return;
        }
        Poco::XML::NodeIterator it(partialViewNode, Poco::XML::NodeFilter::SHOW_ALL);
        auto pNode = it.nextNode();
        while(pNode) {
            _Body->appendChild(pNode);
            pNode = it.nextNode();
        }

    }
    catch(Poco::Exception & exception) {
        printf("Error LayoutBuilder::AddViewContent: %s\n", exception.displayText().c_str());
        return;
    }

    //_Body->appendChild(contentNode);
}

void LayoutBuilder::AddTag(const XString & name, const AttributeList & attributes)
{
    ElementPtr tag = _Document->createElement(name);
    _Head->appendChild(tag);
    for(auto it = attributes.begin(), _end = attributes.end(); it != _end; it++) {
        tag->setAttribute(it->first, it->second);
    }
}

void LayoutBuilder::AddScriptLink(const XString & relativePath)
{
    ElementPtr script = _Document->createElement("script");
    script->setAttribute("src", relativePath + ".js");
    script->setAttribute("type", "text/javascript");
    _Head->appendChild(script);
}

void LayoutBuilder::AddScriptText(const XString & text)
{
    ElementPtr script = _Document->createElement("script");
    XTextPtr textData = _Document->createTextNode(text);
    script->setAttribute("type", "text/javascript");
    script->appendChild(textData);
    _Body->appendChild(script); 
}

void LayoutBuilder::AddCSSLink(const XString & relativePath)
{
    ElementPtr link = _Document->createElement("link");
    link->setAttribute("href", relativePath + ".css");
    link->setAttribute("rel", "stylesheet");
    link->setAttribute("type", "text/css");
    _Head->appendChild(link);
}

void LayoutBuilder::WriteStream(XOStream & ostream) const
{
    Poco::XML::DOMWriter writer;
	writer.setNewLine("\n");
	writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);
	writer.writeNode(ostream, _Document);
}