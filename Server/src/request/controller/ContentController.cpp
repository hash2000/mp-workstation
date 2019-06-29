#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>

#include "ContentController.h"
#include "../route/context/WorkContext.h"

ContentController::ContentController(WorkContext * context) 
    : BaseController(context) {

}

void ContentController::handleRequest(
    Poco::Net::HTTPServerRequest& request, 
    Poco::Net::HTTPServerResponse& response)
{
    if (request.getChunkedTransferEncoding())
		response.setChunkedTransferEncoding(true);
	else if (request.getContentLength() != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
		response.setContentLength(request.getContentLength());
	
	auto contentType = request.getContentType();
	if (contentType.length() == 0) {
		Poco::Path path(_Context->_RelativePath);
		auto extension = path.getExtension();
		if (extension == "ico") {
			contentType = "image/x-icon";
		}
	}
	response.sendFile(_Context->_RelativePath, contentType);  
}