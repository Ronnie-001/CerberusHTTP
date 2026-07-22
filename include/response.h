#ifndef RESPONSE_H 
#define RESPONSE_H

#include <string>

#include "request.h"

namespace cerberus 
{
class Response 
{
public:
    Response(const cerberus::Request& req); 

    void setStatus();
    void setHeader();
    void setBody();
    void setContentType();
    
    void getDate();
    int getContentLength(); 
    
private:
    std::string _status_line;
    std::unordered_map<std::string, std::string> _headers;
    std::string _body;
};
}

#endif // !RESPONSE_H
#define RESPONSE_H
