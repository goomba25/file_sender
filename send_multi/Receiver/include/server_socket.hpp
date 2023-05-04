#include "socket.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

struct Packet{
    int size;
    char buffer[BUF_SIZE];
};

class ServerSocket : public Socket
{
private:
    int client_sock;
    char buffer[BUF_SIZE];

public:
    bool BindSocket(uint16_t port);
    bool ListenSocket(int count);
    bool AcceptSocket();
    void CloseListenSocket();
    int GetSocket();
};
