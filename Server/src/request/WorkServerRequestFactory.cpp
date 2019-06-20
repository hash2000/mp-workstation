#include <stdafx.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "WorkServerRequestFactory.h"

#include "controller/HomeController.h"

Poco::Net::HTTPRequestHandler* WorkServerRequestFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
{
    if (request.getURI() == "/Home/Index" && 
        request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
        return new HomeController;
    }
    return nullptr;
}