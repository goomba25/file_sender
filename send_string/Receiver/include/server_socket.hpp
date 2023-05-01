#include "socket.hpp"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

class ServerSocket : public Socket
{
private:
    int client_sock;
    char buffer[BUF_SIZE];

public:
    bool BindSocket(uint16_t port);
    bool ListenSocket(int count);
    bool AcceptSocket();
    void RecvMessage();
    void CloseAcceptSocket();
    void CloseListenSocket();
};
