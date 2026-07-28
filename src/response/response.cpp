#include "response.h"
#include "constants.h"
#include "request.h"
#include <immintrin.h>
#include <utility>

cerberus::Response::Response(const cerberus::Request& req) {}

void cerberus::Response::setStatus(cerberus::HttpStatus status)
{
    _status = status;
}

void cerberus::Response::setHeader(cerberus::ResponseHeader header, const std::string&& value)
{
    std::string val = std::move(value);
    _headers.insert({ header, val });
}

void cerberus::Response::setBody() {}

void cerberus::Response::getDate()
{}
