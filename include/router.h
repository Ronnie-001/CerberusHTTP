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
        
        /**
         * @brief: Used for checking method of the HTTP request.
         * one of GET, POST, PUT, DELETE.
         *
         */
        void checkStatusCode();
            
        /**
         * @brief: Idenitfies if the resource requested from the client exists 
         * on the server.
         * @returns true or false if the resources exists.
         */
        bool identifyResource();
    
        /**
         * @brief: Retrives the resource off the server.
         * @returns the requested webpage as a raw string.
         */
        std::string getResource();
        
        /**
         * @brief: appropriatley routes the given request to the correct resouce.
         */
        void routeRequest();
};

#endif // !ROUTER_H
