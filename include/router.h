#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"
#include <string_view>

namespace cerberus 
{
class Router 
{
public:
    Router();
    
    void checkHttpMethod(const cerberus::Request& request);
    
    // Checks if the resource actually exists on the server.
    bool verifyResource();
    
    // Functions for handling different HTTP methods.
    void getResource();
    
    void handleGetRequest(std::string_view path);

    void handlePutRequest(std::string_view path);

    void handlePostRequest(std::string_view path);

    void handleDeleteRequest(std::string_view path);
};
}

#endif // !ROUTER_H
