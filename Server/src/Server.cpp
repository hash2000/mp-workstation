#include <stdafx.h>
#include "Server.h"

#include "app/appInstance.h"

#include "request/WorkServerRequestFactory.h"

#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/SecureServerSocket.h>
#include <Poco/Net/ServerSocket.h>


WorkstationServerApp::WorkstationServerApp()
{
}

WorkstationServerApp::~WorkstationServerApp()
{
}

void WorkstationServerApp::initialize(Poco::Util::Application &self)
{
    loadConfiguration(); // load default configuration files, if present
    ServerApplication::initialize(self);
}

void WorkstationServerApp::uninitialize()
{
    ServerApplication::uninitialize();
}

void WorkstationServerApp::defineOptions(Poco::Util::OptionSet &options)
{
    ServerApplication::defineOptions(options);

    // options.addOption(
    //     Poco::Util::Option("help", "h", "display help information on command line arguments")
    //         .required(false)
    //         .repeatable(false));
}

void WorkstationServerApp::handleOption(const std::string &name, const std::string &value)
{
    ServerApplication::handleOption(name, value);
}

int WorkstationServerApp::main(const std::vector<std::string> &args)
{
    // get parameters from configuration file
    unsigned short port = (unsigned short)config().getInt("WorkstationServer.port", 9980);

    auto parameters = new Poco::Net::HTTPServerParams;
    parameters->setKeepAlive(true);
    parameters->setMaxThreads(6);

    Poco::Net::ServerSocket srvSocket(port);

    Poco::Net::HTTPServer server(new WorkServerRequestFactory,
        srvSocket, parameters);
    server.start();

    // wait for CTRL-C or kill
    waitForTerminationRequest();
    // Stop the HTTPServer
    server.stop();


    return Application::EXIT_OK;
}

int main(int argc, char **argv)
{
    // auto instance = appInstance::get();
    // if (!instance->Initialize())
    //     return 1L;
    // instance->Process();
    // instance->Shutdown();
    WorkstationServerApp app;
    return app.run(argc, argv);
}