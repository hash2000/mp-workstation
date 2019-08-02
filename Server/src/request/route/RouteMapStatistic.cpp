#include <stdafx.h>
#include "RouteMapStatistic.h"

#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>


RouteMapStatistic::RouteMapStatistic() 
{
}

RouteMapStatistic::~RouteMapStatistic()
{
    auto & app = Poco::Util::Application::instance();
    std::string message = "RouteMap::GetWorkContext: " + _Route + " ";
    if (!_ErrorMessage.empty()) {
        message += _ErrorMessage;
        app.logger().error(message);
        return;
    }

    if (_CacheState == CacheUnknown) {
        message += "(cache unknown)";
    }
    else if (_CacheState == CacheController) {
        message += "(registered controller)";
    }
    else if (_CacheState == CacheUpdate) {
        message += "(cache update)";
    }
    else if (_CacheState == CacheLoad) {
        message += "(cache load)";
    }
    else if (_CacheState == CacheUse) {
        message += "(cache use [" + std::to_string(_UseCount) + "])";
    }

    // if (_CacheState == CacheUpdate || _CacheState == CacheUse) {
    //     message += " Source DateTime: " + Poco::DateTimeFormatter::format(_SourceModifiedDate,
    //         Poco::DateTimeFormat::ISO8601_FORMAT);
    //     message += " Cache DateTime: " + Poco::DateTimeFormatter::format(_CacheModifiedDate,
    //         Poco::DateTimeFormat::ISO8601_FORMAT);   
    // }

    app.logger().information(message);
}