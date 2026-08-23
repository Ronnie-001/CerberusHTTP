#include <chrono>
#include <cstring>
#include <format>
#include <string>
#include <utility>
#include <ctime>
#include <immintrin.h>
#include "nlohmann/json.hpp"

#include "response.h"
#include "constants.h"
#include "request.h"

#define SERVER_NAME "Cerberus"

cerberus::Response::Response(const cerberus::Request& req) : _request(req) {}

void cerberus::Response::setStatus(cerberus::HttpStatus status)
{
    _status = status;
}

void cerberus::Response::constructStartLine() 
{
    // TODO: Add start line into Request object.
    _start_line = _request.version + " " + _request.resource_path + " " + cerberus::getHttpStatusString(_status);
}

void cerberus::Response::setHeader(cerberus::ResponseHeader header, const std::string&& value)
{
    _headers.insert({ header, std::move(value) });
}

void cerberus::Response::setHeaderMetadata() 
{
    setHeader(cerberus::ResponseHeader::CONNECTION, "close");
    setHeader(cerberus::ResponseHeader::CONTENT_TYPE, "application/json");
    setHeader(cerberus::ResponseHeader::DATE, getCurrentDate());
    setHeader(cerberus::ResponseHeader::CONTENT_LENGTH, std::to_string(getContentLength()));
    setHeader(cerberus::ResponseHeader::SERVER, SERVER_NAME);
    setHeader(cerberus::ResponseHeader::DATE, getCurrentDate());

    setHeader(cerberus::ResponseHeader::CONTENT_TYPE, "application/json");
}

void cerberus::Response::setBody(const nlohmann::json& json) 
{
    _body = json.dump();
}

std::size_t cerberus::Response::getContentLength() 
{
    return std::strlen(_body.c_str());
}

std::string cerberus::Response::getCurrentDate()
{
    std::time_t res = std::time(nullptr);
    std::string time_str = std::asctime(std::localtime(&res));
    const std::chrono::zoned_time zt{std::chrono::current_zone(), std::chrono::system_clock::now()};
    
    // Extract the timezone abbrieviation and return
    return time_str + " " + std::format("{:%Z}", zt);
}

void cerberus::Response::constructResponse() 
{
    setStatus(cerberus::HttpStatus::OK);
    constructStartLine();
    _final_res += _start_line + "\r\n";

    setHeaderMetadata();
    // 2. Add HTTP headers by looping through map
    for (const auto& [header, value] : _headers) {
        _final_res +=  getResponseHeaderString(header) + value + "\r\n";
    }
    
    _final_res += "\r\n";
    // 3. Add body.
    _final_res += _body;
}

std::string cerberus::Response::getResponse() const { return _final_res; }
