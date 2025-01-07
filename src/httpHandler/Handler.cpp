#include "./Handler.h"

PathLinker::PathLinker(std::string pPath, std::string (*pFptr)(std::map<std::string, std::string> &m))
{
    path = pPath;
    fPtr = pFptr;
}

PathListener::PathListener()
{
}
std::string PathListener::processPath(std::string currentPath)
{
    std::size_t locationIfParamsExist = currentPath.find("?");
    std::string pathWithOutParams;
    Response response;
    if (locationIfParamsExist == std::string::npos)
    {
        pathWithOutParams = currentPath;
    }
    else
    {
        pathWithOutParams = currentPath.substr(0, locationIfParamsExist);
    }
    for (int i = 0; i < pathsListenTo.size(); i++)
    {
        if (pathsListenTo[i].getPath() == pathWithOutParams) // da fehlen die parameter
        {
            std::map<std::string, std::string> m = filterParams(currentPath);
            std::string response = pathsListenTo[i].fPtr(m);
            return response;
        }
    }
    return HTTP::Response().notFound();
}
void PathListener::addNewPath(PathLinker linker)
{
    pathsListenTo.push_back(linker);
}
std::map<std::string, std::string> PathListener::filterParams(std::string params)
{
    std::map<std::string, std::string> resultSet;
    params = params.substr(params.find("?") + 1, params.length());
    std::vector<std::string> paramsStrVector;
    std::size_t locationOfDelimiter;
    while ((locationOfDelimiter = params.find("&")) != std::string::npos)
    {
        paramsStrVector.push_back(std::string(params.substr(0, locationOfDelimiter)));
        params = params.erase(0, locationOfDelimiter + 1);
    }
    if (!params.empty())
    {
        paramsStrVector.push_back(params);
    }
    // process vector
    for (int i = 0; i < paramsStrVector.size(); i++)
    {
        std::size_t locationEqual;
        if ((locationEqual = paramsStrVector[i].find("=")) != std::string::npos)
        {
            resultSet.insert(std::pair<std::string, std::string>(paramsStrVector[i].substr(0, locationEqual), paramsStrVector[i].substr(locationEqual + 1, paramsStrVector[i].length())));
        }
    }
    return resultSet;
}
