#ifndef ROUTER_H
#define ROUTER_H

#include <string_view>

#include "data.h"
#include "request.h"

namespace cerberus 
{
class Router 
{
public:
    Router(cerberus::Data& data);
    
    void checkHttpMethod(const cerberus::Request& request);
    
    // Checks if the resource actually exists on the server.
    bool verifyResource(std::string_view path);
    
    // Functions for handling different HTTP methods.
    void getResource();
    
    void handleGetRequest(const cerberus::Request& request);

    void handlePutRequest(const cerberus::Request& request);

    void handlePostRequest(const cerberus::Request& request);

    void handleDeleteRequest(const cerberus::Request& request);

private:
    cerberus::Data _data_handler;
};
}

#endif // !ROUTER_H
