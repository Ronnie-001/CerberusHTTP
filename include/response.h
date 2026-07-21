#ifndef RESPONSE_H 
#define RESPONSE_H

#include <string>

namespace cerberus 
{
class Response 
{
public:

    void setStatus();
    void setHeader();
    void setBody();
    void setContentType();
    
    void getDate();
    int getContentLength(); 
    
private:
    std::string _body;
};
}

#endif // !RESPONSE_H
#define RESPONSE_H
