#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "WorkServerRequestFactory.h"

#include "controller/HomeController.h"

WorkServerRequestFactory::WorkServerRequestFactory(WorkContext * context) 
    : _Context(context) {

}

Poco::Net::HTTPRequestHandler* WorkServerRequestFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
{
    if (request.getURI() == "/Home/Index" && 
        request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
        return new HomeController(_Context);
    }
    return nullptr;
}