#ifndef RESPONSE_H 
#define RESPONSE_H

#include <string>

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
    // Set standard HTTP headers, like date, time, Server, etc.
    void setHeader();
    void setBody();
    void setContentType();
    
    void getDate();

    // get the content length of the final response.
    int getContentLength(); 

    std::string getResponse() const;
    
private:
    std::string _status_line;
    std::unordered_map<std::string, std::string> _headers;
    std::string _body;

    std::string _final_res;
};
}

#endif // !RESPONSE_H
#define RESPONSE_H
