#pragma once
#include <string>
#include <vector>
#include <any>
#include <functional>
#include <iostream>
#include <map>
#include "../http/HTTP.h"
// vllt ne callback funktion als parameter ?
// der body der response sollte json sein
//

class PathLinker
{
public:
    PathLinker();
    PathLinker(std::string path, std::string (*pFptr)(std::map<std::string, std::string> &m));
    std::string getPath() { return path; }
    std::string (*fPtr)(std::map<std::string, std::string> &m);

private:
    // MethodenPointer ptr;
    std::string path;
};
class PathListener
{
private:
    std::vector<PathLinker> pathsListenTo;
    std::map<std::string, std::string> filterParams(std::string params);

public:
    PathListener();
    ~PathListener();
    void addNewPath(PathLinker pLinker);
    std::string processPath(std::string currentPath);
};
