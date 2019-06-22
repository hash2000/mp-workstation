#include <stdafx.h>
#include "LayoutBuilder.h"

void LayoutBuilder::Initialize()
{
    _Document = new Poco::XML::Document;
    _Html = _Document->createElement("html");
    _Head = _Document->createElement("head");
    _Body = _Document->createElement("body");

    AddMeta(AttributeList {
        { "http-equiv", "X-UA-Compatible" },
        { "content", "IE=edge" },
    });

    AddMeta(AttributeList {
        { "name", "viewport" },
        { "content", "width=device-width, initial-scale=1, maximum-scale=10, user-scalable=yes" },
    });

    _Document->appendChild(_Html);
    _Html->appendChild(_Head);
    _Html->appendChild(_Body);


}

void LayoutBuilder::AddMeta(const AttributeList & attributes)
{
    for(auto it = attributes.begin(), _end = attributes.end(); it != _end; it++) {
        ElementPtr meta = _Document->createElement("meta");
        meta->setAttribute(it->first, it->second);
        _Head->appendChild(meta);
    }
}