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
    // add to std::unordered_map
    void setHeader(cerberus::ResponseHeader header, const std::string&& value);
    void setBody(const nlohmann::json& json);
    // application/json
    void setContentType();
    // get the content length of the final response.
    int getContentLength(); 
    void getCurrentDate();
    
    std::string getResponse() const;
    
private:
    cerberus::HttpStatus _status;
    std::string _status_line;
    std::unordered_map<cerberus::ResponseHeader, std::string> _headers;
    std::string _body;

    std::string _final_res;
};
}

#endif // !RESPONSE_H
#define RESPONSE_H
