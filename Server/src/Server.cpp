#include <stdafx.h>
#include "Server.h"

#include "request/WorkServerRequestFactory.h"
#include "request/RouteMap.h"

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
    // load default configuration files, if present
    loadConfiguration(); 
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
    // Получение параметров из конфигурационного файла
    auto port = (unsigned short)config().getInt("WorkstationServer.port", 9980);
    auto threadCount = (int)config().getInt("WorkstationServer.thread.count", 6);
    auto parameters = new Poco::Net::HTTPServerParams;

    parameters->setKeepAlive(true);
    parameters->setMaxThreads(threadCount);

    _RouteMap = new RouteMap; 
    _RouteMap->Initialize();

    // Создание незащищённого сокета для прослушивания подключений
    Poco::Net::ServerSocket srvSocket(port);
    // Создание сервера
    Poco::Net::HTTPServer server(new WorkServerRequestFactory(_RouteMap),
        srvSocket, parameters);

    // Запуск сервера
    server.start();
    // ожидание сигнала остановки CTRL-C или kill
    waitForTerminationRequest();
    // Остановка сервера
    server.stop();


    delete _RouteMap;


    return Application::EXIT_OK;
}

int main(int argc, char **argv)
{
    WorkstationServerApp app;
    return app.run(argc, argv);
}