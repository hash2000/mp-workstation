#include <stdafx.h>
#include "RouteMapStatistic.h"

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
    else if (_CacheState == CacheUpdate) {
        message += "(cache update)";
    }
    else if (_CacheState == CacheLoad) {
        message += "(cache load)";
    }
    else if (_CacheState == CacheUse) {
        message += "(cache use)";
    }

    app.logger().information(message);
}