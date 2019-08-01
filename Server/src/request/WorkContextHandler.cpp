#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

#include "WorkContextHandler.h"
#include "route/context/WorkContext.h"

WorkContextHandler::WorkContextHandler(WorkContext *context)
    : _Context(context)
{
}

WorkContextHandler::~WorkContextHandler()
{
    if (_Context->_UseCount > 0)
        _Context->_UseCount --;
}

void WorkContextHandler::handleRequest(
    Poco::Net::HTTPServerRequest &request,
    Poco::Net::HTTPServerResponse &response)
{
    try {

        if (request.getChunkedTransferEncoding())
            response.setChunkedTransferEncoding(true);
        else if (request.getContentLength() != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
            response.setContentLength(request.getContentLength());

        auto contentType = request.getContentType();
        if (contentType.empty()) {
            contentType = _Context->_ContentType;
        }

        response.setContentType(contentType);    
        auto &responseStream = response.send();

        if (_Context->_Layout) {
            _Context->_Layout->WriteStream(responseStream);
            return;
        }

        if (_Context->_FileBuffer.empty()) {
            return;
        }

        response.set("Last-Modified", Poco::DateTimeFormatter::format(_Context->_ReadTime, 
            Poco::DateTimeFormat::HTTP_FORMAT));
        response.setChunkedTransferEncoding(false);
#if defined(POCO_HAVE_INT64)	
        response.setContentLength64(_Context->_FileBufferSize);
#else
        response.setContentLength(static_cast<int>(_Context->_FileBufferSize));
#endif  

        responseStream << _Context->_FileBuffer;
        
        // auto copySize = Poco::StreamCopier::copyStream(_Context->_FileBuffer, 
        //     responseStream);
        // if (copySize != _Context->_FileBufferSize) {
        //     auto & app = Poco::Util::Application::instance();
        //     app.logger().warning("Filestream for source " +
        //         _Context->_Path.toString() + " read " +
        //         std::to_string(copySize) + " instead " + 
        //         std::to_string(_Context->_FileBufferSize));
        // }
    }
    catch (Poco::Exception & exception) {
        auto & app = Poco::Util::Application::instance();
        app.logger().error("WorkContextHandler::handleRequest:exception " +
            exception.message());
    }
}
