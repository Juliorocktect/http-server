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
        closeSocket();
        return -1;
    }
    if (bindToPort() == -1)
        return -2;
    if (listen(sockfd,SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen to port";
        closeSocket();
        return -3;
    }
    //accepting connections in new thread
    acceptClientConnection();
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
    while (1)// var running is true
    {
        struct sockaddr_in clientAddr;
        socklen_t clientSize = sizeof(clientAddr);
        int clientSocket_fd = accept(sockfd,(sockaddr*) &clientAddr,&clientSize);
        if (clientSocket_fd == -1)//Error handling
        {
            std::cerr << "[Error] Failed to accept connection\n";
        }
        //handle connection
        std::thread(&Server::handleClientConnection,this,clientSocket_fd,(sockaddr* )&clientAddr).detach();
    }
    return 1;// return nicht vergessen :) sonst core dumpedd
}
Response Server::reciveData(int clientSocket)
{
    char buf[4096];
    memset(buf, 0, 4096);
    std::string recievedData;
    int receivedBytes = recv(clientSocket,buf,sizeof(buf),0);
    if (receivedBytes == -1)
    {
        std::cerr << "[Error] in transmitting data\n";
        Response res;
        res.exitCode = -1;
        return res;
    }
    if (receivedBytes == 0)
    {
        //std::cout << "[Info] Disconnected\n";// oder der client sendet nix 
        Response res;
        res.exitCode = 1;
        return res;
    }
    //process bytes
    std::string request = std::string(buf, 0, receivedBytes);
    Response result = this->processBytes(request); 
    return result;
}
Response Server::processBytes(std::string request)
{
    HTTP::HeaderRequest *req = new HTTP::HeaderRequest();
    req->processRequest(request);
    Response response;
    if (req->connection.compare("keep-alive")){
        Keep_alive keepAlive;
        keepAlive.useKeepAlive = 1;
        if (req->keepAlive.length() != 0)
        {
            keepAlive.max = 5;
            keepAlive.timeout = 5;
        }else{
            // use values from header atribute Keep-Alive:
        }
        response.keepAlive = keepAlive;
    }
    response.HTTP_Response = pathListener->processPath(req->path);
    return response;
}
void Server::handleClientConnection(int clientSocket_fd,sockaddr* client_addr)
{
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    char client_ip[INET_ADDRSTRLEN];
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    memset(client_ip, 0, INET_ADDRSTRLEN);
    sockaddr_in *clientAddr= (sockaddr_in*) client_addr;
    if (getnameinfo(client_addr, sizeof(client_addr),host,NI_MAXHOST,service,NI_MAXSERV,0) == 0)
    {
        std::cout << "[Info] Connected\n Host:\t" << host << "\nservice:\t"<<service << "\n";
    }
    else // in case of disconnecting base information saved sth security i guess normal behaviour
    {
            inet_ntop(AF_INET, &clientAddr->sin_addr, host, NI_MAXHOST);
            inet_ntop(AF_INET, &clientAddr->sin_addr, client_ip, INET_ADDRSTRLEN);
            std::cout << host << " connected on port:\t " << ntohs(clientAddr->sin_port)<< "\nWith IP:\t" << client_ip << std::endl;
    }
    //first contact -> check for keep-alive
    Response response = reciveData(clientSocket_fd);
    sendData(clientSocket_fd,response.HTTP_Response);
    if (response.keepAlive.useKeepAlive)
    {
        int requestsDone = response.keepAlive.max;
        std::promise<int> timerPromise;
        std::future<int> timerFuture = timerPromise.get_future();
        std::thread timerThread(&Server::startTimer,this,std::move(timerPromise),5);
        while (requestsDone > 0 && (timerFuture.wait_for(std::chrono::seconds(0)) != std::future_status::ready))
        {
            Response response = reciveData(clientSocket_fd);
            sendData(clientSocket_fd,response.HTTP_Response);
            requestsDone--;
        }
        timerThread.join();
        
    }
    while (0) //promised not fullfilled
    {
        Response res = reciveData(clientSocket_fd);
        sendData(clientSocket_fd,res.HTTP_Response);
        //check for connection keep-alive and timeout
    }
    std::cout << "disconnect" << std::endl;
    close(clientSocket_fd);
}
void Server::sendData(int clientSocket,std::string data)
{
    send(clientSocket,data.c_str(),data.length(),0);
}
void Server::startTimer(std::promise<int>&& promise,int duration)
{
        while (duration)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        duration--;
        std::cout<< duration << std::endl;
    }
    promise.set_value(1);
}