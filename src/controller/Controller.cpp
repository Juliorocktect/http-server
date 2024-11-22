#include "./Controller.h"

std::string homeResponse(std::map<std::string, std::string> &m)
{
    HTTP::Response res;
    std::ifstream file("/home/julio/Documents/code/http/src/controller/Response.html");
    std::string fileContent;
    if (file.is_open())
    {
        std::stringstream sstr;
        sstr << file.rdbuf();
        fileContent = sstr.str();
    }
    res.body = fileContent;
    res.statusCode = HTTP::Codes().OK;
    res.connection = "close";
    res.contentType = "text/html; charset=utf-8";
    res.contentLength = fileContent.size();
    return res.buildResponse();
}
std::string jsonResponse(std::map<std::string, std::string> &m)
{
    HTTP::Response res;
    return res.buildResponse();
}
void linkFunctions(PathListener *lis)
{
    lis->addNewPath(PathLinker(std::string("/lul"), &homeResponse));
    lis->addNewPath(PathLinker(std::string("/test"), &processParams));
}
std::string processParams(std::map<std::string, std::string> &m)
{
    HTTP::Response res;
    if (m.count("id"))
    {
        res.body = "{ id :" + m.at("id") + "}";
    }
    if (!m.count("id"))
    {
        HTTP::Response badRes;
        badRes.body = std::string("");
        badRes.contentLength = 0;
        badRes.connection = "close";
        badRes.statusCode = HTTP::Codes().BAD_REQUEST;
        return badRes.buildResponse();
    }
    res.statusCode = HTTP::Codes().OK;
    res.connection = "close";
    res.contentType = "text/json; charset=utf-8";
    res.contentLength = res.body.size();
    return res.buildResponse();
}
std::string buildJson()
{
}