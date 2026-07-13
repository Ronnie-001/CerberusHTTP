#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <vector>

#include "router.h"
#include "constants.h"
#include "request.h"
#include "data.h"
#include "generation.h"
#include "tcp.h"

cerberus::Router::Router() {}

void cerberus::Router::checkHttpMethod(const cerberus::Request& request, cerberus::Data& data) 
{
    // Validate the resource that is trying to be accessed first.    
    if (!verifyResource(request.resource_path)) throw std::invalid_argument("[ERROR] Requested resource could not be found.");

    switch (request.method) {
        case cerberus::HttpMethod::GET:
            handleGetRequest(request, data);
            break;
        case cerberus::HttpMethod::PUT:
            handlePutRequest(request, data);
            break;
        case cerberus::HttpMethod::POST:
            handlePostRequest(request, data);
            break;
        case cerberus::HttpMethod::DELETE:
            handleDeleteRequest(request, data);
            break;
        default:
            throw std::invalid_argument("[ERROR] No HTTP method provided."); 
    }
}

bool cerberus::Router::verifyResource(std::string_view path) 
{ 
    std::filesystem::path full_path = std::filesystem::current_path();
    full_path += path;

    std::filesystem::file_status status = std::filesystem::status(full_path);
    
    if (!std::filesystem::status_known(status)) {
        std::cout << "[ERROR] Unkown file status.";
        return false;
    }

    return std::filesystem::exists(full_path);
}


std::string cerberus::Router::getResource(const std::string& str, char delim) 
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string store;
    
    while (std::getline(ss, store, '/')) {
        result.push_back(store);
    }
    
    return result[result.size() - 1];
}

void cerberus::Router::handleGetRequest(const cerberus::Request& request, cerberus::Data& data) 
{

    cerberus::TcpListener::sendResponse(request.fd);
}

void cerberus::Router::handlePutRequest(const cerberus::Request& request, cerberus::Data& data) 
{
    std::uint64_t id = cerberus::generation::generateId();

    auto map = request.body.value();
    User user = { map["username"], map["password"] };
    data.addUser(id, user);

    cerberus::TcpListener::sendResponse(request.fd);
}

void cerberus::Router::handlePostRequest(const cerberus::Request& request, cerberus::Data& data) 
{

    cerberus::TcpListener::sendResponse(request.fd);
}

void cerberus::Router::handleDeleteRequest(const cerberus::Request& request, cerberus::Data& data) 
{

    cerberus::TcpListener::sendResponse(request.fd);
}
