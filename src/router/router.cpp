#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "router.h"
#include "constants.h"
#include "request.h"
#include "data.h"

cerberus::Router::Router(const cerberus::Data& data_handler) : _data_handler(data_handler) {}

void cerberus::Router::checkHttpMethod(const cerberus::Request& request) 
{
    // Validate the resource that is trying to be accessed first.    
    if (!verifyResource(request.resourcePath)) throw std::invalid_argument("[ERROR] Requested resource could not be found.");

    switch (request.method) {
        case cerberus::HttpMethod::GET:
            handleGetRequest(request.resourcePath, request);
        case cerberus::HttpMethod::PUT:
            handlePutRequest(request.resourcePath, request);
        case cerberus::HttpMethod::POST:
            handlePostRequest(request.resourcePath, request);
        case cerberus::HttpMethod::DELETE:
            handleDeleteRequest(request.resourcePath, request);
        default:
            throw std::invalid_argument("[ERROR] No HTTP method provided."); 
    }
}

bool cerberus::Router::verifyResource(std::string_view path) 
{ 
    std::filesystem::path p = path;
    std::filesystem::file_status status = std::filesystem::status(p);
    
    if (!std::filesystem::status_known(status)) {
        std::cout << "[ERROR] Unkown file status.";
        return false;
    }

    return std::filesystem::exists(path);
}

void cerberus::Router::handleGetRequest(std::string_view path, const cerberus::Request& request) {}

void cerberus::Router::handlePutRequest(std::string_view path, const cerberus::Request& request) 
{
    // Get the KV pairs from the message body.
    // Use this to construct the User struct.
    // use nlohmann libraray to convert it to a JSON array.
    // Once you have the JSON, use std::ofstream to write to users.json.
    
    auto map = request.body.value();
    User user = { map["username"], map["password"] };

    _data_handler.addUser(user);
}

void cerberus::Router::handlePostRequest(std::string_view path, const cerberus::Request& request) {}

void cerberus::Router::handleDeleteRequest(std::string_view path, const cerberus::Request& request) {}
