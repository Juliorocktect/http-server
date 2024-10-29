#pragma once
#include <string>
#include <vector>
// vllt ne callback funktion als parameter ?
//der body der response sollte json sein
//

class PathLinker {
    public: 
        std::string path;
        const char* (*fPtr) ();
        PathLinker();
        PathLinker(std::string path,const char* (*pFpTr));
};
class PathListener{
    //linking between funtion + path
    public:
        std::vector<PathLinker> pathsListenTo;
        PathListener();
        ~PathListener();
        void processPath(std::string currentPath);
};


void requestListener(std::string path)
{
}