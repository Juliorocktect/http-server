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
#include <thread>
#include <chrono>

class Server
{
public:
    Server(const char *host, int port,PathListener* pPathListener);
    ~Server();
    void sendData(int clientSocket,std::string data);
    int start();
    void closeSocket();

private:
    PathListener* pathListener;
    int sockfd,port;
    const char* host;
    struct sockaddr_in serverAddr;
    void createSocket();
    int bindToPort();
    void handleClientConnection(int clientSocket_fd,struct sockaddr* client_addr);
    int acceptClientConnection();
    std::string reciveData(int clientSocket);
    std::string processBytes(std::string request);
};

// TODO: add thread support
int startServer(int port, PathListener *listener);