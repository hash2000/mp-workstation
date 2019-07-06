#include <stdafx.h>

#include <Poco/SAX/InputSource.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeList.h>
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

    _Document->appendChild(_Html);
    _Html->appendChild(_Head);
    _Html->appendChild(_Body);

    AddTag("meta", AttributeList {
        { "http-equiv", "X-UA-Compatible" },
        { "content", "IE=edge" },
    });

    AddTag("meta", AttributeList {
        { "name", "viewport" },
        { "content", "width=device-width, initial-scale=1, maximum-scale=10, user-scalable=yes" },
    });

    AddTag("link", AttributeList {
        { "href", "/Content/favicon.ico" },
        { "rel", "shortcut icon" },
        { "type", "image/x-icon" },
    });
    

    AddScriptLink(
        "/Content/Scripts/Libs/ExtJs/6.2.1/build/ext-all-debug.js"
    );

    AddCSSLink(
        "/Content/Scripts/Libs/ExtJsThemes/theme2019/Theme.css"
    );

    AddScriptLink(
        "/Content/Scripts/Libs/ExtJs/6.2.1/build/classic/theme-triton/theme-triton.js"
    );

    AddScriptLink(
        "/Content/Scripts/Libs/ExtJs/6.2.1/packages/exporter/build/classic/exporter-debug.js"
    );

    AddScriptLink(
        "/Content/Scripts/Libs/ExtJs/6.2.1/build/classic/locale/locale-ru.js"
    );


    AddCSSLink(
        "/Content/Styles/Site.css"
    );

    AddViewContent(context);

}

void LayoutBuilder::AddViewContent(WorkContext * context)
{
    Poco::XML::InputSource source(context->_Path.toString());    
    
    try{
        Poco::XML::DOMParser parser;
        // parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, false);
	    // parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACE_PREFIXES, false);
		Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&source);
	
        auto clonedNode = _Document->importNode(pDoc->documentElement(), true);   
        auto rootNode = clonedNode->getNodeByPath("/");
        if (!rootNode) {
            printf("Error LayoutBuilder::AddViewContent partialView nodes not found\n");
            return;
        }

        if(rootNode->nodeName() != "partialView") {
            printf("Error LayoutBuilder::AddViewContent the root node must have a name \'partialView\'");
        }

        auto nodes = rootNode->childNodes();
        for(unsigned long i = 0, _end = nodes->length(); i < _end; i++) {
            auto pNode = nodes->item(i);
            if (!pNode || pNode->nodeType() != Poco::XML::Node::ELEMENT_NODE)
                continue;
            _Body->appendChild(pNode);
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
    _Head->appendChild(script);
    script->setAttribute("src", relativePath);
    script->setAttribute("type", "text/javascript");
}

void LayoutBuilder::AddScriptText(const XString & text)
{
    ElementPtr script = _Document->createElement("script");
    XTextPtr textData = _Document->createTextNode(text);
    _Body->appendChild(script); 
    script->setAttribute("type", "text/javascript");
    script->appendChild(textData);
}

void LayoutBuilder::AddCSSLink(const XString & relativePath)
{
    ElementPtr link = _Document->createElement("link");
    _Head->appendChild(link);
    link->setAttribute("href", relativePath);
    link->setAttribute("rel", "stylesheet");
    link->setAttribute("type", "text/css");
}

void LayoutBuilder::WriteStream(XOStream & ostream) const
{
    Poco::XML::DOMWriter writer;
	writer.setNewLine("\n");
	writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT | Poco::XML::XMLWriter::CANONICAL_XML);
	writer.writeNode(ostream, _Document);
}