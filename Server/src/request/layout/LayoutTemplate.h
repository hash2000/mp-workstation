#ifndef __LAYOUTTEMPLATE_H__
#define __LAYOUTTEMPLATE_H__ 

#include <Poco/DOM/Document.h>
#include <Poco/AutoPtr.h>
#include <map>
#include <string>


class LayoutTemplate
{
public:
    void Initialize();
    Poco::AutoPtr<Poco::XML::Document> GetTemplate(const std::string & name) const;

private:
    std::map<std::string, Poco::AutoPtr<Poco::XML::Document>> 
        _Templates;
};

#endif // !__LAYOUTTEMPLATE_H__