#pragma once
#include <string>
#include <vector>
#include <any>
#include <functional>
#include <iostream>
// vllt ne callback funktion als parameter ?
//der body der response sollte json sein
//

class PathLinker
{
public:
    PathLinker();
    PathLinker(std::string path, std::string (*pFptr)(std::vector<std::any>));
    std::string getPath() { return path; }
    std::string (*fPtr)(std::vector<std::any> args);

private:
    //MethodenPointer ptr;
    std::string path;
};
class PathListener
{
private:
    std::vector<PathLinker> pathsListenTo;
    std::vector<std::any> filterParams(std::string params);

public:
    PathListener();
    ~PathListener();
    void addNewPath(PathLinker pLinker);
    void processPath(std::string currentPath);
};
