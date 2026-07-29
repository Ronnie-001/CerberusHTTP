#include <chrono>
#include <cstring>
#include <format>
#include <utility>
#include <ctime>
#include <immintrin.h>
#include "nlohmann/json.hpp"

#include "response.h"
#include "constants.h"
#include "request.h"

cerberus::Response::Response(const cerberus::Request& req) {}

void cerberus::Response::setStatus(cerberus::HttpStatus status)
{
    _status = status;
}

void cerberus::Response::setHeader(cerberus::ResponseHeader header, const std::string&& value)
{
    _headers.insert({ header, std::move(value) });
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
    
    // Extract the timezone abbrieviation and return,
    return std::format("{:%Z}", zt);
}
