#include "HTTP.h"
namespace HTTP
{
    Response::Response() {}
    std::string Response::buildResponse()
    {
        std::string result;
        this->Server = std::string("juli/jaja");
        result += "HTTP/1.1 " + std::to_string(statusCode) + " OK\n";
        return result;
    }
};