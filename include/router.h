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
    Router();
    
    void checkHttpMethod(const cerberus::Request& request, cerberus::Data& data);
    
    // Checks if the resource actually exists on the server.
    bool verifyResource(std::string_view path);
    
    // Used for grabbing the resource from the end of the provided resource path.
    std::string getResource(const std::string& str, char delim);
    
    // Functions for handling different HTTP methods.
    void handleGetRequest(const cerberus::Request& request, cerberus::Data& data);

    void handlePutRequest(const cerberus::Request& request, cerberus::Data& data);

    void handlePostRequest(const cerberus::Request& request, cerberus::Data& data);

    void handleDeleteRequest(const cerberus::Request& request, cerberus::Data& data);

private:
    cerberus::Data _data_handler;
};
}

#endif // !ROUTER_H
