#ifndef __WORKCONTEXT_H__
#define __WORKCONTEXT_H__

#include "../../layout/LayoutBuilder.h"

#include <Poco/Path.h>
#include <Poco/LocalDateTime.h>

#include <functional>
#include <string>
#include <vector>
#include <atomic>


class WorkContext
{
public:
    LayoutBuilder * _Layout;
    std::vector<char> _Buffer;
    std::string _ContentType;
    std::atomic_uint32_t _UseCount;
    Poco::Path _Path;
    Poco::LocalDateTime _ReadTime;
};


#endif // !__WORKCONTEXT_H__