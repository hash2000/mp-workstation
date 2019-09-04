#ifndef __Database_H__
#define __Database_H__

#include <Poco/Foundation.h>
#include <string>
#include <memory>


class Foundation_API Database
{
public:
    static std::shared_ptr<Database> Create(
        const std::string & path,
        const std::string & name);

    virtual bool Initialize() = 0;
};


#endif
