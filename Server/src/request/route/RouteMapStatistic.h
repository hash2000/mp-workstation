#ifndef __ROUTEMAPSTATISTIC_H__
#define __ROUTEMAPSTATISTIC_H__

#include <Poco/LocalDateTime.h>

#include <string>

class RouteMapStatistic
{
public:
    enum CacheState {
        CacheUnknown,
        CacheUpdate,
        CacheLoad,
        CacheUse
    };

public:
    RouteMapStatistic();
    ~RouteMapStatistic();

    void SetCacheState(CacheState state) {
        _CacheState = state;
    }

    void SetRoute(const std::string & route) {
        _Route = route;
    }

    void SetSourceModifiedDate(const Poco::LocalDateTime & date) {
        _SourceModifiedDate = date;
    }

    void AppendErrorMessage(const std::string & message) {
        _ErrorMessage += message + " ";
    }

    void IsAreaView(bool isAreaView) {
        _IsAreaView = isAreaView;
    }

private:
    std::string _Route;
    std::string _ErrorMessage;
    Poco::LocalDateTime _SourceModifiedDate;
    CacheState _CacheState = CacheUnknown;
    bool _IsAreaView = false;
};


#endif // !__ROUTEMAPSTATISTIC_H__