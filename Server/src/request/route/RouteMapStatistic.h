#ifndef __RouteMapStatistic_H__
#define __RouteMapStatistic_H__

#include <Poco/LocalDateTime.h>

#include <string>

class RouteMapStatistic
{
public:
    enum CacheState {
        CacheUnknown,
        CacheController,
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

    void SetCacheModifiedDate(const Poco::LocalDateTime & date) {
        _CacheModifiedDate = date;
    }

    void AppendErrorMessage(const std::string & message) {
        _ErrorMessage += message + " ";
    }

    void IsAreaView(bool isAreaView) {
        _IsAreaView = isAreaView;
    }

    void SetUseCount(unsigned int count) {
        _UseCount = count;
    }

private:
    std::string _Route;
    std::string _ErrorMessage;
    Poco::LocalDateTime _SourceModifiedDate;
    Poco::LocalDateTime _CacheModifiedDate;
    CacheState _CacheState = CacheUnknown;
    unsigned int _UseCount = 0;
    bool _IsAreaView = false;
};


#endif // !__RouteMapStatistic_H__