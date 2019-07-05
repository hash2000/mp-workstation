#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>

#include "WorkContextController.h"
#include "../route/context/WorkContext.h"


void WorkContextController::handleRequest(
    Poco::Net::HTTPServerRequest& request, 
    Poco::Net::HTTPServerResponse& response) 
{
    if (request.getChunkedTransferEncoding())
		response.setChunkedTransferEncoding(true);
	else if (request.getContentLength() != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
		response.setContentLength(request.getContentLength());

    auto contentType = request.getContentType();
    if (contentType.empty()) {
        contentType = _Context->_ContentType;
    }
	
    response.setContentType(contentType);
    auto& responseStream = response.send();

    if (_Context->_Layout) {
        _Context->_Layout->WriteStream(responseStream);
        return;
    }

    response.sendFile(_Context->_Path.toString(), contentType);  
}
