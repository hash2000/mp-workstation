#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>

#include "HomeController.h"


void HomeController::handleRequest(
    Poco::Net::HTTPServerRequest& request, 
    Poco::Net::HTTPServerResponse& response)
{
    if (request.getChunkedTransferEncoding())
		response.setChunkedTransferEncoding(true);
	else if (request.getContentLength() != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
		response.setContentLength(request.getContentLength());
	
	response.setContentType(request.getContentType());
	
	//std::istream& istr = request.stream();
	auto& ostr = response.send();
    ostr << "<html>";
    ostr << "<body>";
    ostr << "<h3>тестовая строка</h3>";  
    ostr << "</body>";
    ostr << "</html>";
    //Poco::StreamCopier::copyStream(istr, ostr);
}