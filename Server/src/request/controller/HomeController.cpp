#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>

#include "HomeController.h"
#include "../WorkContext.h"

HomeController::HomeController(WorkContext * context) 
    : _Context(context) {

}

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
    _Context->Layout->WriteStream(ostr);
    //Poco::StreamCopier::copyStream(istr, ostr);
}