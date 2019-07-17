#include <stdafx.h>
#include "LayoutTemplate.h"

#include <Poco/DirectoryIterator.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/Exception.h>


void LayoutTemplate::Initialize()
{
    for (Poco::DirectoryIterator it(Poco::Path("Web/Layout")), _end; it != _end; it ++ ){
        Poco::Path pathinfo(it->path());
        Poco::XML::InputSource source(it->path());    
        Poco::XML::DOMParser parser;

        try {            
            _Templates[pathinfo.getBaseName()] = parser.parse(&source);
        }
        catch(Poco::Exception & exception) {
            printf("Error LayoutTemplate::Initialize: %s\n", exception.displayText().c_str());
            return;
        }
    } 

}


Poco::AutoPtr<Poco::XML::Document> LayoutTemplate::GetTemplate(const std::string & name) const
{
    auto tpl = _Templates.find(name);
    if (tpl == _Templates.end()) {
        return Poco::AutoPtr<Poco::XML::Document>();
    }

    return tpl->second;
}