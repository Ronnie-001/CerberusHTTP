#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"

namespace cerberus 
{
class Router 
{
public:
    Router(const cerberus::Request& request);
    
    void checkHttpMethod();
    
    // Checks if the resource actually exists on the server.
    bool verifyResource();
    
    // Functions for handling different HTTP methods.
    void getResource();
    
    void handleGetRequest();

    void handlePutRequest();

    void handlePostRequest();

    void handleDeleteRequest();

private:
    cerberus::Request _request;
};
}

#endif // !ROUTER_H
