#include "./Handler.h"

PathListener::PathListener()
{

}
void PathListener::processPath(std::string currentPath)
{
    for (int i = 0;i < pathsListenTo.size();i++){
        if (pathsListenTo[i].path == currentPath){
            //pathsListenTo[i].method call;
            return;
        }
    }
}