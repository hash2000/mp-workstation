#ifndef __HTMLLAYOUT_H__
#define __HTMLLAYOUT_H__


#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Attr.h>
#include <Poco/DOM/NamedNodeMap.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/XML/XMLWriter.h>
#include <Poco/SAX/InputSource.h>

#include <string>
#include <map>


class HtmlLayout
{
public:
    using DocPtr = Poco::XML::AutoPtr<Poco::XML::Document>;
    using XOStream = Poco::XML::XMLByteOutputStream;
    using ElementPtr = Poco::XML::AutoPtr<Poco::XML::Element>;
    using AttrPtr = Poco::XML::AutoPtr<Poco::XML::Attr>;
    using XString = Poco::XML::XMLString;
    using XTextPtr = Poco::XML::AutoPtr<Poco::XML::Text>;
    using AttributeList = std::map<XString, XString>;    

public:
    void ResetDocument();

    std::string ReadAttribute(Poco::XML::Node * node, 
        const std::string & name) const;
    void WriteStream(XOStream & ostream) const;

protected:
    DocPtr _Document;
    ElementPtr _Html, _Head, _Body;
};


#endif // !__HTMLLAYOUT_H__
