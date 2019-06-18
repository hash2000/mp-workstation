#include <stdafx.h>
#include "WorkServer.h"
#include "WorkServerRequestFactory.h"

#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/SecureServerSocket.h>

std::thread WorkServer::Start()
{
    return std::thread([] {
        auto parameters = new Poco::Net::HTTPServerParams;
        parameters->setKeepAlive(true);
        parameters->setMaxThreads(6);

        Poco::Net::SecureServerSocket srvSocket(0);

        Poco::Net::HTTPServer server(new WorkServerRequestFactory,
            srvSocket, parameters);
        server.start();
    });
}
