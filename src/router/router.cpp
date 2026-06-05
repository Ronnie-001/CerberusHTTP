#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "router.h"
#include "constants.h"
#include "request.h"

cerberus::Router::Router() {}

void cerberus::Router::checkHttpMethod(const cerberus::Request& request) 
{
    // Validate the resource that is trying to be accessed first.    
    if (!verifyResource(request.resourcePath)) throw std::invalid_argument("[ERROR] Requested resource could not be found.");

    switch (request.method) {
        case cerberus::HttpMethod::GET:
            handleGetRequest(request.resourcePath);
        case cerberus::HttpMethod::PUT:
            handlePutRequest(request.resourcePath);
        case cerberus::HttpMethod::POST:
            handlePostRequest(request.resourcePath);
        case cerberus::HttpMethod::DELETE:
            handleDeleteRequest(request.resourcePath);
        default:
            throw std::invalid_argument("[ERROR] No HTTP method provided."); 
    }
}

bool cerberus::Router::verifyResource(std::string_view path) 
{ 
    std::filesystem::path p = path;
    std::filesystem::file_status status = std::filesystem::status(p);

    if (!std::filesystem::status_known(status)) {
        std::cerr << "[ERROR] Unkown file status.";
        return false;
    }

    return std::filesystem::exists(path);
}

void cerberus::Router::handleGetRequest(std::string_view path) 
{

}

void cerberus::Router::handlePutRequest(std::string_view path) {}

void cerberus::Router::handlePostRequest(std::string_view path) {}

void cerberus::Router::handleDeleteRequest(std::string_view path) {}
