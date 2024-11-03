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
    res.statusCode = HTTP::Codes().ok;
    res.connection = "close";
    res.contentType = "text/html; charset=utf-8";
    res.contentLength = fileContent.size();
    return res.buildResponse();
}
void linkFunctions(PathListener *lis)
{
    lis->addNewPath(PathLinker(std::string("/lul"), &homeResponse));
}