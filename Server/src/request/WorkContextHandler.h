#ifndef __WorkContextHandler_H__
#define __WorkContextHandler_H__

#include <Poco/Net/HTTPRequestHandler.h>

class WorkContext;
class DatabaseManager;


class WorkContextHandler: public Poco::Net::HTTPRequestHandler
{
public:
    WorkContextHandler(WorkContext * context,
        DatabaseManager * dbManager);
    virtual ~WorkContextHandler() ;

    void handleRequest(
        Poco::Net::HTTPServerRequest& request, 
        Poco::Net::HTTPServerResponse& response) override;

protected:
    WorkContext * _Context;
    DatabaseManager * _DbManager;
};

#endif // !__WorkContextHandler_H__