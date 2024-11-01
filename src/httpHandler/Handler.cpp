#include "./Handler.h"

PathLinker::PathLinker(std::string pPath, std::string (*pFptr)(std::vector<std::any>))
{
    path = pPath;
    fPtr = pFptr;
}

PathListener::PathListener()
{
}
void PathListener::processPath(std::string currentPath)
{
    for (int i = 0; i < pathsListenTo.size(); i++)
    {
        if (pathsListenTo[i].getPath() == currentPath) //da fehlen die parameter
        {
            filterParams(currentPath);
            std::vector<std::any> v;
            v.push_back(3);
            pathsListenTo[i].fPtr(v);
            return;
        }
    }
}
void PathListener::addNewPath(PathLinker linker)
{
    pathsListenTo.push_back(linker);
}
std::vector<std::any> PathListener::filterParams(std::string params)
{
    std::vector<std::any> resultSet;
    std::cout << "PARAMS" << params;
    std::string::size_type begin = params.find('?');
    if (begin == std::string::npos)
    {
        return resultSet;
    }
    params = params.substr(begin, params.length());
    std::cout << "[INFO:]\t" << params << "\n";
    std::vector<std::string> paramsStr;
}