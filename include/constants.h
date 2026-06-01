#ifndef CONSTANTS_H
#define CONSTANTS_H

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
    TRACE
};

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
