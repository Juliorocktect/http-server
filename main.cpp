#include <iostream>
#include <string>
#include "src/http/HTTP.h"
#include "src/server/Server.h"
#include "src/httpHandler/Handler.h"
#include "src/controller/Controller.h"
#include <vector>
#include <any>
#include <map>
std::string add(std::map<std::string, std::string> &m)
{
    if (m.count("id")) // error if not present
    {
        std::cout << "[From function call]" << m.at("id") << std::endl;
    }
    return ""; // core dumped wenn kein return da ist <:(
}

int main(int argc, char const *argv[])
{
    PathListener *listen = new PathListener();
    linkFunctions(listen);
    listen->addNewPath(PathLinker(std::string("/user"), &add));
    return startServer(9090, listen);
}
