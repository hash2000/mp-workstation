#ifndef __LAYOUTBUILDER_H__
#define __LAYOUTBUILDER_H__

#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Attr.h>
#include <Poco/XML/XMLWriter.h>
#include <map>

class LayoutBuilder
{
public:
    using DocPtr = Poco::XML::AutoPtr<Poco::XML::Document>;
    using ElementPtr = Poco::XML::AutoPtr<Poco::XML::Element>;
    using AttrPtr = Poco::XML::AutoPtr<Poco::XML::Attr>;
    using XString = Poco::XML::XMLString;

    using AttributeList = std::map<XString, XString>;

public:
    void Initialize();
    void AddMeta(const AttributeList & attributes);
    void AddScriptLink(const XString & relativePath);
    void AddCSSLink(const XString & relativePath);


private:
    DocPtr _Document;
    ElementPtr _Html;
    ElementPtr  _Head;
    ElementPtr  _Body;
};



#endif // !__LAYOUTBUILDER_H__