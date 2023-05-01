#include "socket.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

class ClientSocket : public Socket
{
private:
    struct sockaddr_in server_addr;

public:
    bool StringToBinary(char *ip, uint16_t port);
    bool ConnectSocket();
    void SendFile(char *file_name);
    void CloseSocket();
};
