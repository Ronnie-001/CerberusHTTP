#ifndef REQUEST_H
#define REQUEST_H

#include "constants.h"
#include <string>
#include <unordered_map>
#include <optional>

namespace cerberus 
{
struct Request 
{
    // Start line
    cerberus::HttpMethod method;
    std::string resourcePath;
    std::string version; 

    // request headers
    std::unordered_map<std::string, std::string> headers;

    // message body
    std::optional<std::unordered_map<std::string, std::string>> body;

};

cerberus::HttpMethod getHttpMethod(const std::string& str);

}

// Pretty printer for the request struct.
std::ostream& operator<<(std::ostream& out, const cerberus::Request& request); 


#endif // ! REQUEST_H
