#ifndef __WORKCONTEXT_H__
#define __WORKCONTEXT_H__

#include "../../layout/LayoutBuilder.h"
#include "../../../db/manager/DatabaseManager.h"


#include <Poco/Path.h>
#include <Poco/LocalDateTime.h>
#include <Poco/File.h>

#include <functional>
#include <string>
#include <vector>
#include <atomic>


class WorkContext
{
public:
    LayoutBuilder * _Layout;
    DatabaseManager * _DbManager;
    std::string _ContentType;
    std::string _FileBuffer;
    std::atomic_uint32_t _UseCount;
    Poco::Path _Path;
    Poco::File::FileSize _FileBufferSize;
    Poco::LocalDateTime _ReadTime;
};


#endif // !__WORKCONTEXT_H__