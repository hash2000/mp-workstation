#ifndef __WORKCONTEXT_H__
#define __WORKCONTEXT_H__

#include "../../layout/LayoutBuilder.h"

#include <Poco/Path.h>
#include <Poco/LocalDateTime.h>
#include <Poco/FileStream.h>
#include <Poco/File.h>

#include <functional>
#include <string>
#include <vector>
#include <atomic>


class WorkContext
{
public:
    LayoutBuilder * _Layout;
    std::string _ContentType;
    std::atomic_uint32_t _UseCount;
    Poco::Path _Path;
    Poco::FileInputStream _FileStream;
    Poco::File::FileSize _FileStreamSize;
    Poco::LocalDateTime _ReadTime;
};


#endif // !__WORKCONTEXT_H__