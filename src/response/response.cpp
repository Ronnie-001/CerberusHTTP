#include "response.h"
#include "constants.h"
#include "nlohmann/json.hpp"
#include "request.h"
#include <ctime>
#include <immintrin.h>
#include <utility>
#include <iostream>

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
    std::string str = json.dump();
    _body = str;
}

void cerberus::Response::getCurrentDate()
{
    std::time_t res = std::time(nullptr);
    std::string time_str = std::asctime(std::localtime(&res));
    std::cout << time_str;
}
