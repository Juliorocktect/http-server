#include "Server.h"
void Server::createSocket()
{
}

int startServer(int port, PathListener *pathListener)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        return -1;
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
    int opt = 1; // reusable ?
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
        // accept a connection
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);

        int clientSocket = accept(sockfd, (sockaddr *)&client, &clientSize);
        if (clientSocket == -1)
        {
            std::cerr << "[Error] Failed to accept connection\n";
            return -4;
        }
        // connection information
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
        // recive msg
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
            // std::cout << std::string(buf, 0, recived) << std::endl;
            // process bytes
            HTTP::HeaderRequest *req = new HTTP::HeaderRequest();
            req->processRequest(std::string(buf, 0, recived));
            std::string response;
            response = pathListener->processPath(req->path);
            send(clientSocket, response.c_str(), response.length(), 0);
            // wenn timer vorhanden warten sons thread schließen und socket schließen
            close(clientSocket);
        }
    }
    close(sockfd);

    return 0;
}

Server::Server(const char *host,int port,PathListener* pPathListener)
{
    this->host = host;
    this->port = port;
    pathListener = pPathListener;
}
int Server::start(){
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd == -1)
    {
        delete &sockfd;
        return -1;
    }
    if (bindToPort() == -1)
        return -2;
    if (listen(sockfd,SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen to port";
        return -3;
    }
    //accepting connections in new thread
    while(1)
    {
        acceptClientConnection();
    }
    closeSocket();
    return 1;
}
void Server::closeSocket()
{
    close(sockfd);
}
Server::~Server(){}
int Server::bindToPort()
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET,host,&serverAddr.sin_addr);
    int opt = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt));
    if (bind(sockfd,(sockaddr*)&serverAddr,sizeof(serverAddr)) == -1)
    {
        std::cerr << "Can't bind to port\n";
        return -1;
    }
    return 1;
}
int Server::acceptClientConnection()
{
    //creating vars for the client
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    int clientSocket = accept(sockfd, (sockaddr*) &client,&clientSize);
    if (clientSocket == -1)//Error handling
    {

        std::cerr << "[Error] Failed to accept connection\n";
        return -4;
    }
    //information about connection
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    if (getnameinfo((sockaddr*)&client,sizeof(client), host, NI_MAXHOST,service,NI_MAXSERV,0) == 0)
    {
        std::cout << "Connected\n";
    } else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl; 
    } 
    // recieve and send data
     char buf[4096];
    while (1){
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
            // std::cout << std::string(buf, 0, recived) << std::endl;
            // process bytes
            HTTP::HeaderRequest *req = new HTTP::HeaderRequest();
            req->processRequest(std::string(buf, 0, recived));
            std::string response;
            response = pathListener->processPath(req->path);
            send(clientSocket, response.c_str(), response.length(), 0);
            // wenn timer vorhanden warten sons thread schließen und socket schließen
        /* std::string response;
        response = reciveData(clientSocket);
        std::cout << response << "\n";
        send(clientSocket,"OK",2,0); */
    }
    // von vorher wiederholen bis auf den verbindungsaufbau

    close(clientSocket);
    return 1;// return nicht vergessen :) sonst core dumpedd
}
std::string Server::reciveData(int clientSocket)
{
    // 1 durchlauf dannach timeout oder so 
    char buf[4096];
    memset(buf, 0, 4096);
    int recived = recv(clientSocket,buf,4096,0);
    if (recived == -1)
    {
        std::cerr << "[Error] in transmitting data\n";
        return "-1";
    }
    if (recived == 0)
    {
        std::cout << "[Info] Disconnected\n";
        return "1";
    }
    //process bytes
    std::string request = std::string(buf, 0, recived);
    std::string result = this->processBytes(request);
    return result;
}
std::string Server::processBytes(std::string request)
{
    std::cout << request;
    HTTP::HeaderRequest *req = new HTTP::HeaderRequest();
    req->processRequest(request);
    std::string response;
    response = pathListener->processPath(req->path);
    return response;
}
void Server::sendData(int clientSocket,std::string data)
{
    send(clientSocket,data.c_str(),data.length(),0);//TODO: Error handling
}