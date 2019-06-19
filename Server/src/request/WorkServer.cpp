#include <stdafx.h>
#include "WorkServer.h"
#include "WorkServerRequestFactory.h"

#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/SecureServerSocket.h>
#include <Poco/Net/ServerSocket.h>

std::thread WorkServer::Start()
{
    return std::thread([] {
        try{
            auto parameters = new Poco::Net::HTTPServerParams;
            parameters->setKeepAlive(true);
            parameters->setMaxThreads(6);

            Poco::Net::ServerSocket srvSocket(1037);

            Poco::Net::HTTPServer server(new WorkServerRequestFactory,
                srvSocket, parameters);
            server.start();
        }
        catch(Poco::Exception * exception) {
            printf("WorkServer thread exception: %s\n", exception->what());
            return;
        }
    });
}
