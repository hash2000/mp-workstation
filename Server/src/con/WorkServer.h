#ifndef __WORKSERVER_H__
#define __WORKSERVER_H__

#include <thread>

class WorkServer
{
public:
    static std::thread Start();   
};


#endif // !__WORKSERVER_H__