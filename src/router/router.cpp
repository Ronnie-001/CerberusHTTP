#include <stdexcept>

#include "router.h"
#include "constants.h"


cerberus::Router::Router(const cerberus::Request& request) : _request(request) 
{
    // TODO: validate the HTTP request path during construction.
}

void cerberus::Router::checkHttpMethod()
{
    switch (_request.method) {
        case cerberus::HttpMethod::GET: 
            handleGetRequest();
        case cerberus::HttpMethod::PUT: 
            handlePutRequest();
        case cerberus::HttpMethod::POST: 
            handlePostRequest();
        case cerberus::HttpMethod::DELETE: 
            handleDeleteRequest();
        default:
            throw std::invalid_argument("[ERROR] Error routing request: HTTP Method not provided.");
            break;
    }
}

void cerberus::Router::handleGetRequest() 
{

}

void cerberus::Router::handlePutRequest() {}

void cerberus::Router::handlePostRequest() {}

void cerberus::Router::handleDeleteRequest() {}
