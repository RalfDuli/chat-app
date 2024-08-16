#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <cerrno>
#include <cstring>

class ChatClient {
    public:
        ChatClient(std::string name, int __id);

        addrinfo *address, *serverInfo;
        addrinfo hints;
        
        std::string name, serverAddress, portNum;
        int id;

        bool sendThread(std::string msg);
        std::string recvThread();
    
    private:
        int sock;
        char buf[1024];

};

#endif