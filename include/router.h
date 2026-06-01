#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"

class Router 
{
public:
    Router(const cerberus::Request& request) : _request(request)
    {}
    
    void checkStatusCode();
        
    bool identifyResource();

    std::string getResource();
    
    void routeRequest();

private:
    cerberus::Request _request;
};

#endif // !ROUTER_H
