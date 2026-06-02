#include "router.h"
#include <stdexcept>

cerberus::Router::Router(const cerberus::Request& request) : _request(request) 
{}

void cerberus::Router::checkHttpMethod()
{
    if (_request.method == cerberus::HttpMethod::NOT_PROVIDED) {
        throw std::invalid_argument("HTTP method not provided.");
    }
    
    if (_request.method == cerberus::HttpMethod::GET) {}

    if (_request.method == cerberus::HttpMethod::PUT) {}

    if (_request.method == cerberus::HttpMethod::POST) {}

    if (_request.method == cerberus::HttpMethod::DELETE) {}

    if (_request.method == cerberus::HttpMethod::PATCH) {}

    if (_request.method == cerberus::HttpMethod::OPTIONS) {}

    if (_request.method == cerberus::HttpMethod::HEAD) {}

    if (_request.method == cerberus::HttpMethod::CONNECT) {}

    if (_request.method == cerberus::HttpMethod::TRACE) {}
}
