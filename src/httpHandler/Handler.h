#pragma once
#include <string>
#include<vector>
// vllt ne callback funktion als parameter ?
//der body der response sollte json sein
//

class PathLinker {
    public: 
        std::string path;
        //(std::string) (*) pointer to path process function
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