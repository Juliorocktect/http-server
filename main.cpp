#include <iostream>
#include <string>
#include "src/http/HTTP.h"
#include "src/server/Server.h"
#include "src/httpHandler/Handler.h"
#include <vector>
#include <any>
std::string add(std::vector<std::any> params)
{
    if (params[0].type() == typeid(int))
    {
        std::cout << "[Info]\t" << std::any_cast<int>(params[0]) << "\n";
    }
    else
    {
        std::cerr << "[Error] falsche typ";
    }
    return ""; //core dumped wenn kein return da ist <:(
}

int main(int argc, char const *argv[])
{
    PathListener *listen = new PathListener();
    listen->addNewPath(PathLinker(std::string("/user"), &add));
    return startServer(9090, listen);
}
