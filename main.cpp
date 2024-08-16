#include <iostream>
#include <thread>

#include "headers/client.h"
#include "headers/server.h"

int main() {
    std::cerr << "Hello, World!" << std::endl;

    ChatServer *server = new ChatServer();
    ChatClient *client = new ChatClient("Bob", 123);

    std::thread t1(&ChatClient::sendThread, client, "Message delivered!\n");
    std::thread t2(&ChatServer::recvThread, server);

    t1.join();
    t2.join();


    return 0;
}