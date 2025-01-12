#include <iostream>
#include <string>
#include "src/http/HTTP.h"
#include "src/server/Server.h"
#include "src/httpHandler/Handler.h"
#include "src/controller/Controller.h"
#include <vector>
#include <any>
#include <map>
#include <thread>
#include <chrono>
#include "src/repo/Repo.h"


int main(int argc, char const *argv[])
{
    PathListener *listen = new PathListener();
    linkFunctions(listen);
    Video vid = getVideoFromDatabase();
    std::cout << vid.title << "\n";
    Server server("127.0.0.1",8080,listen);
    server.start();
    return 1;
}
