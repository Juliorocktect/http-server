#pragma once
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include "../http/HTTP.h"
#include "../httpHandler/Handler.h"

class Server
{
public:
    Server(const char *host, const char *port);
    ~Server();
    int start();
    void stop();

private:
    const char *host;
    const char *port;
    int socket;
    void createSocket();
};
int startServer(int port,PathListener *listener);