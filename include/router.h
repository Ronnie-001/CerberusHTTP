#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"

class Router 
{
private:
    cerberus::Request _request;

public:

    Router(const cerberus::Request& request) : _request(request)
    {}
    
    void checkStatusCode();
        
    bool identifyResource();

    std::string getResource();
    
    void routeRequest();
};

#endif // !ROUTER_H
