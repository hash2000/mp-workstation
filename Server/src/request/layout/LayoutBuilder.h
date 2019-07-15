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

class WorkContext;

class LayoutBuilder
{
public:
    using DocPtr = Poco::XML::AutoPtr<Poco::XML::Document>;
    using ElementPtr = Poco::XML::AutoPtr<Poco::XML::Element>;
    using AttrPtr = Poco::XML::AutoPtr<Poco::XML::Attr>;
    using XString = Poco::XML::XMLString;
    using XTextPtr = Poco::XML::AutoPtr<Poco::XML::Text>;
    using XOStream = Poco::XML::XMLByteOutputStream;

    using AttributeList = std::map<XString, XString>;

public:
    void Initialize(WorkContext * context);
    void AddTag(const XString & name, const AttributeList & attributes);
    void AddScriptLink(const XString & relativePath);
    void AddScriptText(const XString & text);
    void AddCSSLink(const XString & relativePath);

private:
    std::string ReadAttribute(Poco::XML::Node * node, const std::string & name) const;
    void LoadLayout(Poco::AutoPtr<Poco::XML::Document> pDoc);

public:
    void WriteStream(XOStream & ostream) const;

private:
    DocPtr _Document = nullptr;
    ElementPtr _Html;
    ElementPtr  _Head;
    ElementPtr  _Body;
};



#endif // !__LAYOUTBUILDER_H__