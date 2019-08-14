#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/JSON/Parser.h>

#include "WorkContextHandler.h"

#include "route/context/WorkContext.h"
#include "route/RouteMap.h"


WorkContextHandler::WorkContextHandler(RouteMap * routeMap,
        DatabaseManager * dbManager)
    : _RouteMap(routeMap)
    , _DbManager(dbManager)
{
}

WorkContextHandler::~WorkContextHandler()
{
    if (_Context && _Context->_UseCount > 0)
        _Context->_UseCount --;
}

void WorkContextHandler::handleRequest(
    Poco::Net::HTTPServerRequest &request,
    Poco::Net::HTTPServerResponse &response)
{

    _Context = _RouteMap->GetWorkContext(request);
    if (!_Context) {
        return;
    }
  
    try {

        if (request.getChunkedTransferEncoding())
            response.setChunkedTransferEncoding(true);
        else if (request.getContentLength() != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
            response.setContentLength(request.getContentLength());
         
        auto &responseStream = response.send();

        if (_Context->_Controller) {
            auto result = _Context->_Controller->HandleRequest(_DbManager,
                _Context->_RequestParameters);

            if (!result.isNull()) {                
                Poco::JSON::Stringifier::stringify(result,
                    responseStream);
            }
        }
        else if (_Context->_Layout) {
            response.setContentType("text/html");
            _Context->_Layout->WriteStream(responseStream);
        }
        else if (!_Context->_FileBuffer.empty()) {

            response.set("Last-Modified", Poco::DateTimeFormatter::format(_Context->_ReadTime, 
                Poco::DateTimeFormat::HTTP_FORMAT));
            response.setChunkedTransferEncoding(false);
            response.setContentType(_Context->_ContentType); 
#if defined(POCO_HAVE_INT64)	
            response.setContentLength64(_Context->_FileBufferSize);
#else
            response.setContentLength(static_cast<int>(_Context->_FileBufferSize));
#endif  

            responseStream << _Context->_FileBuffer;
        }

    }
    catch (Poco::Exception & exception) {
        auto & app = Poco::Util::Application::instance();
        app.logger().error("WorkContextHandler::handleRequest:exception " +
            exception.message());
    }
}
