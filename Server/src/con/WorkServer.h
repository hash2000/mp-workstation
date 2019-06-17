#ifndef __WORKSERVER_H__
#define __WORKSERVER_H__

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Net/TCPServerParams.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Timestamp.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/Exception.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>


class WorkServer: public Poco::Util::ServerApplication
	/// The main application class.
	///
	/// This class handles command-line arguments and
	/// configuration files.
	/// Start the TimeServer executable with the help
	/// option (/help on Windows, --help on Unix) for
	/// the available command line options.
	///
	/// To use the sample configuration file (TimeServer.properties),
	/// copy the file to the directory where the TimeServer executable
	/// resides. If you start the debug version of the TimeServer
	/// (TimeServerd[.exe]), you must also create a copy of the configuration
	/// file named TimeServerd.properties. In the configuration file, you
	/// can specify the port on which the server is listening (default
	/// 9911) and the format of the date/time string sent back to the client.
	///
	/// To test the TimeServer you can use any telnet client (telnet localhost 9911).
{

};


#endif // !__WORKSERVER_H__