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

    std::string getResource();

private:
    cerberus::Request _request;
    
};
}

#endif // !ROUTER_H
