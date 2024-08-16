#include "headers/server.h"

ChatServer::ChatServer() {

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_NUMERICHOST;

    ipAddress = "127.0.0.1";
    portNum = "8080";

    if ((getaddrinfo(ipAddress.c_str(), portNum.c_str(), &hints, &serverInfo)) != 0) {
        std::cerr << "Error calling getaddrinfo(). " << strerror(errno) << std::endl;
        exit(1);
    }

    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, portNum.c_str(), &hints, &clientInfo) != 0) {
        std::cerr << "Error calling getaddrinfo(). " << strerror(errno) << std::endl;
        exit(1);
    }

    sockaddr_in *addr_in = (sockaddr_in *) serverInfo->ai_addr;
    char *s = inet_ntoa(addr_in->sin_addr);
    std::cout << "Server address: " << s << std::endl;

    serverSock = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

    if (serverSock < 0) {
        std::cerr << "Error establishing the server socket. " << strerror(errno) << std::endl;
        exit(1);
    }

    int optval = 1;
    if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        std::cerr << "Error no setsockopt. " << strerror(errno) << std::endl;
        exit(1);
    } 

    if (bind(serverSock, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1) {
        std::cerr << "Error binding. " << strerror(errno) << std::endl;
        exit(1);
    }
}

bool ChatServer::sendThread(std::string msg) {
    const char *msgPointer = msg.c_str();

    send(serverSock, msgPointer, (msg).length(), 0);
    return true;
}

std::string ChatServer::recvThread() {
    if (listen(serverSock, 5) != -1)
        std::cout << "Server listened for an oncoming connection. " << std::endl;
    else
        std::cerr << "Error listening for oncoming connections. " << strerror(errno) << std::endl;

    socklen_t addrLen = clientInfo->ai_addrlen;

    sockaddr *connectionAddr;

    int connectionSock = accept(serverSock, NULL, NULL);

    if (connectionSock < 0) {
        std::cerr << "Error making a connection socket. " << strerror(errno) << std::endl;
    }

    recv(connectionSock, buf, sizeof(buf), 0);
    std::cout << buf;
    
    return (std::string) buf;
}