#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace cerberus
{
enum class HttpMethod 
{
    GET,
    PUT,
    POST,
    DELETE,
    PATCH,
    OPTIONS,
    HEAD,
    CONNECT,
    TRACE,

    // Used in case no HTTP method is provided.
    NOT_PROVIDED
};

inline std::string getHttpMethodString(cerberus::HttpMethod method)
{
    if (method == cerberus::HttpMethod::GET) return "GET";
    if (method == cerberus::HttpMethod::PUT) return "PUT";
    if (method == cerberus::HttpMethod::POST) return "POST";
    if (method == cerberus::HttpMethod::DELETE) return "DELETE";
    if (method == cerberus::HttpMethod::PATCH) return "PATCH";
    if (method == cerberus::HttpMethod::OPTIONS) return "OPTIONS";
    if (method == cerberus::HttpMethod::HEAD) return "HEAD";
    if (method == cerberus::HttpMethod::CONNECT) return "CONNECT";
    if (method == cerberus::HttpMethod::TRACE) return "TRACE";
    
    return "NOT PROVIDED";
}

inline cerberus::HttpMethod getHttpMethod(const std::string &str)
{
    if (str == "GET") return cerberus::HttpMethod::GET;
    if (str == "PUT") return cerberus::HttpMethod::PUT;
    if (str == "POST") return cerberus::HttpMethod::POST;
    if (str == "DELETE") return cerberus::HttpMethod::DELETE;
    if (str == "PATCH") return cerberus::HttpMethod::PATCH;
    if (str == "OPTIONS") return cerberus::HttpMethod::OPTIONS;
    if (str == "HEAD") return cerberus::HttpMethod::HEAD;
    if (str == "CONNECT") return cerberus::HttpMethod::CONNECT;
    if (str == "TRACE") return cerberus::HttpMethod::TRACE;

    return cerberus::HttpMethod::NOT_PROVIDED;
}

enum class HttpStatus
{
    // Successful response codes
    OK                      = 200,
    CREATED                 = 201,
    ACCEPTED                = 202,
    NO_CONTENT              = 204,

    // Redirection response codes
    MOVED_PERMANENTLY       = 301,
    FOUND                   = 302,
    SEE_OHTER               = 303,
    NOT_MODIFIED            = 304,
    TEMPORARY_REDIRECT      = 307,
    PERMANENT_REDIRECT      = 308,

    // Client error response codes
    BAD_REQUEST             = 400,
    UNAUTHORIZED            = 401,
    FORBIDDEN               = 403,
    NOT_FOUND               = 404,
    METHOD_NOT_ALLOWED      = 405,
    NOT_ACCEPTABLE          = 406,
    REQUEST_TIMEOUT         = 408,

    // Server error response codes
    INTERNAL_SERVER_ERROR   = 500,
    NOT_IMPLEMENTED         = 501,
    BAD_GATEWAY             = 502,
    SERVICE_UNAVALIABLE     = 503
};

}
#endif // !CONSTANTS_H
