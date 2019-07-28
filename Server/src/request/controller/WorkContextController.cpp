#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

#include "WorkContextController.h"
#include "../route/context/WorkContext.h"

WorkContextController::WorkContextController(WorkContext *context)
    : _Context(context)
{
}

WorkContextController::~WorkContextController()
{
    if (_Context->_UseCount > 0)
        _Context->_UseCount --;
}

void WorkContextController::handleRequest(
    Poco::Net::HTTPServerRequest &request,
    Poco::Net::HTTPServerResponse &response)
{
    if (request.getChunkedTransferEncoding())
        response.setChunkedTransferEncoding(true);
    else if (request.getContentLength() != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
        response.setContentLength(request.getContentLength());

    auto contentType = request.getContentType();
    if (contentType.empty())
    {
        contentType = _Context->_ContentType;
    }

    response.setContentType(contentType);
    
    auto &responseStream = response.send();

    if (_Context->_Layout)
    {
        _Context->_Layout->WriteStream(responseStream);
        return;
    }

    response.set("Last-Modified", Poco::DateTimeFormatter::format(_Context->_ReadTime, 
        Poco::DateTimeFormat::HTTP_FORMAT));
    response.setChunkedTransferEncoding(false);
  #if defined(POCO_HAVE_INT64)	
	response.setContentLength64(_Context->_FileStreamSize);
#else
	response.setContentLength(static_cast<int>(_Context->_FileStreamSize));
#endif  
    
    Poco::StreamCopier::copyStream(_Context->_FileStream, responseStream);
}
