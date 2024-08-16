#include "headers/client.h"

ChatClient::ChatClient(std::string __name, int __id) {

    name = __name;
    id = __id;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        std::cerr << "Error establishing the client socket. " << strerror(errno) << std::endl;
        exit(1);
    }

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    serverAddress = "127.0.0.1";
    portNum = "8080";

    if (getaddrinfo(serverAddress.c_str(), portNum.c_str(), &hints, &serverInfo) != 0) {
        std::cerr << "Error calling getaddrinfo(). " << strerror(errno) << std::endl;
        exit(1);
    }
}

bool ChatClient::sendThread(std::string msg) {
    usleep(500);
    if (connect(sock, serverInfo->ai_addr, serverInfo->ai_addrlen) == 0)
        std::cerr << "The client " << name << " has established a connection with the server." << std::endl;
    else
        std::cerr << "Error establishing a connection between the client " << name << " and the server. " << strerror(errno) << std::endl;

    const char *msgPointer = msg.c_str();

    if (send(sock, msgPointer, msg.length(), 0) < 0) {
        return false;
    }
    return true;
}

std::string ChatClient::recvThread() {
    recv(sock, buf, sizeof(buf), 0);
    return (std::string) buf;
}