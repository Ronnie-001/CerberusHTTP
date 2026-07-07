#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <cstdint>

#include "router.h"
#include "constants.h"
#include "request.h"
#include "data.h"
#include "generation.h"

cerberus::Router::Router() {}

void cerberus::Router::checkHttpMethod(const cerberus::Request& request, cerberus::Data& data) 
{
    std::cout << "[LOGS] in the checkHttpMethod! " << '\n';
    // Validate the resource that is trying to be accessed first.    

    if (!verifyResource(request.resourcePath)) throw std::invalid_argument("[ERROR] Requested resource could not be found.");

    switch (request.method) {
        case cerberus::HttpMethod::GET:
            handleGetRequest(request, data);
        case cerberus::HttpMethod::PUT:
            handlePutRequest(request, data);
        case cerberus::HttpMethod::POST:
            handlePostRequest(request, data);
        case cerberus::HttpMethod::DELETE:
            handleDeleteRequest(request, data);
        default:
            throw std::invalid_argument("[ERROR] No HTTP method provided."); 
    }
}

bool cerberus::Router::verifyResource(std::string_view path) 
{ 
    std::filesystem::path full_path = std::filesystem::current_path();
    full_path += path;
    std::cout << "[LOGS] CURRENT PATH: " << std::filesystem::current_path() << '\n';
    std::cout << "[LOGS] FULL PATH: " << full_path << '\n';

    std::filesystem::file_status status = std::filesystem::status(full_path);
    
    if (!std::filesystem::status_known(status)) {
        std::cout << "[ERROR] Unkown file status.";
        return false;
    }

    return std::filesystem::exists(full_path);
}

void cerberus::Router::handleGetRequest(const cerberus::Request& request, cerberus::Data& data) {}

void cerberus::Router::handlePutRequest(const cerberus::Request& request, cerberus::Data& data) 
{
    // TODO: Generate the id here.
    std::uint64_t id = cerberus::generation::generateId();

    auto map = request.body.value();
    User user = { map["username"], map["password"] };
    data.addUser(id, user);

    // TODO: Add the HTTP response after handling request.
}

void cerberus::Router::handlePostRequest(const cerberus::Request& request, cerberus::Data& data) {}

void cerberus::Router::handleDeleteRequest(const cerberus::Request& request, cerberus::Data& data) {}
