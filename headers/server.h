#ifndef SERVER_H
#define SERVER_H

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <cerrno>
#include <cstring>

class ChatServer {
    public:
        ChatServer();

        addrinfo *serverInfo, *clientInfo;
        addrinfo hints;

        std::string ipAddress;
        std::string portNum;

        bool sendThread(std::string msg);
        std::string recvThread();
    
    private:
        int serverSock;
        char buf[1024];

};

#endif