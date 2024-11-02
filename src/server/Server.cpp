#include "Server.h"
void Server::createSocket()
{
}

int startServer(int port, PathListener *pathListener)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        return 1;
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
    int opt = 1; //reusable ?
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (bind(sockfd, (sockaddr *)&hint, sizeof(hint)) == -1)
    {
        std::cout << "Cant bind to port\n";
        return -2;
    }
    if (listen(sockfd, SOMAXCONN) == -1)
    {
        std::cout << "Cant listen\n";
        return -3;
    }
    while (1)
    {
        //accept a connection
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);

        int clientSocket = accept(sockfd, (sockaddr *)&client, &clientSize);
        if (clientSocket == -1)
        {
            std::cerr << "[Error] Failed to accept connection\n";
            return -4;
        }
        //connection information
        char host[NI_MAXHOST];
        char service[NI_MAXSERV];
        memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);

        if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
        {
            std::cout << "[Info] Connected\n";
        }
        else
        {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
        }

        char buf[4096];
        //recive msg
        while (1)
        {
            memset(buf, 0, 4096);
            int recived = recv(clientSocket, buf, 4096, 0);
            if (recived == -1)
            {
                std::cerr << "[Error] error in transmitting Data\n";
                break;
            }
            if (recived == 0)
            {
                std::cout << "Disconnected";
                break;
            }
            //std::cout << std::string(buf, 0, recived) << std::endl;
            //process bytes
            HTTP::HeaderRequest *req = new HTTP::HeaderRequest();
            req->processRequest(std::string(buf, 0, recived));
            req->printFile();
            pathListener->processPath(req->path);
            HTTP::Response response = HTTP::Response();
            response.statusCode = 200;
            std::string msg = response.buildResponse();
            send(clientSocket, msg.c_str(), msg.length(), 0);
            close(clientSocket);
            //close(sockfd);
            break;
        }
    }
    close(sockfd);
    return 0;
}