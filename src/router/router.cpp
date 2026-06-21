#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <cstdint>

#include "router.h"
#include "constants.h"
#include "request.h"
#include "data.h"

cerberus::Router::Router() {}

void cerberus::Router::checkHttpMethod(const cerberus::Request& request, cerberus::Data& data, std::uint64_t id) 
{
    std::cout << "[LOGS] in the checkHttpMethod! " << '\n';
    // Validate the resource that is trying to be accessed first.    
    // if (!verifyResource(request.resourcePath)) throw std::invalid_argument("[ERROR] Requested resource could not be found.");
    if (!verifyResource(request.resourcePath)) throw std::invalid_argument("[ERROR] Requested resource could not be found.");

    switch (request.method) {
        case cerberus::HttpMethod::GET:
            handleGetRequest(request, data, id);
        case cerberus::HttpMethod::PUT:
            handlePutRequest(request, data, id);
        case cerberus::HttpMethod::POST:
            handlePostRequest(request, data, id);
        case cerberus::HttpMethod::DELETE:
            handleDeleteRequest(request, data, id);
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

void cerberus::Router::handleGetRequest(const cerberus::Request& request, cerberus::Data& data, const std::uint64_t id) {}

void cerberus::Router::handlePutRequest(const cerberus::Request& request, cerberus::Data& data, const std::uint64_t id) 
{
    auto map = request.body.value();
    User user = { map["username"], map["password"] };
    data.addUser(id, user);
}

void cerberus::Router::handlePostRequest(const cerberus::Request& request, cerberus::Data& data, const std::uint64_t id) {}

void cerberus::Router::handleDeleteRequest(const cerberus::Request& request, cerberus::Data& data, const std::uint64_t id) {}
