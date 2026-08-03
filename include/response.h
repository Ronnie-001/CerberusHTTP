#ifndef RESPONSE_H 
#define RESPONSE_H

#include <string>

#include "nlohmann/json.hpp"
#include "request.h"
#include "constants.h"

namespace cerberus 
{
class Response 
{
public:
    Response(const cerberus::Request& req); 

    // Set the status of the HTTP response 
    void setStatus(cerberus::HttpStatus status);

    void constructStartLine();
    
    // add to std::unordered_map
    void setHeader(cerberus::ResponseHeader header, const std::string&& value);
    void setHeaderMetadata();
    void setBody(const nlohmann::json& json);
    // defualt is application/json
    void setContentType();

    // get the content length of the final response.
    std::size_t getContentLength(); 
    std::string getCurrentDate();
    
    // Create the final response with the start line, headers, and response body.
    void constructResponse();
    
    std::string getResponse() const;
    
private:
    cerberus::HttpStatus _status;
    std::string _start_line;
    std::unordered_map<cerberus::ResponseHeader, std::string> _headers;
    std::string _body;
    std::string _final_res;

    cerberus::Request _request;
};
}

#endif // !RESPONSE_H
#define RESPONSE_H
