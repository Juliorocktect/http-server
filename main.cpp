#include <iostream>
#include <string>
#include "src/http/HTTP.h"
#include "src/server/Server.h"
#include "src/httpHandler/Handler.h"

std::string add(){
    return std::string("functioncalled");
}

int main(int argc, char const *argv[])
{
    /*  HTTP::Date *dat = new HTTP::Date(HTTP::WeekDay::Sat, 23, HTTP::Month::Okt, 2024);
    HTTP::HeaderRequest headerR = HTTP::HeaderRequest();
    headerR.processRequest("/home/julio/Documents/code/http/Request.txt");
    headerR.printFile(); */
    PathListener *lis = new PathListener();
    
    //lis->pathsListenTo.push_back(PathLinker(std::string("/user"),&add);
    return startServer(9090,);
}
