#include <stdafx.h>
#include "HtmlLayout.h"

std::string HtmlLayout::ReadAttribute(Poco::XML::Node * node, const std::string & name) const
{
    auto attributes = node->attributes();
    auto attrib = attributes->getNamedItem(name);
    if (!attrib) 
        return std::string();
    return attrib->getNodeValue();
}

void HtmlLayout::WriteStream(XOStream & ostream) const
{
    Poco::XML::DOMWriter writer;
	writer.setNewLine(Poco::XML::XMLWriter::NEWLINE_CRLF);
	writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT | 
        Poco::XML::XMLWriter::CANONICAL_XML);
	writer.writeNode(ostream, _Document);
}

void HtmlLayout::ResetDocument()
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
}