#include "socket.hpp"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class ClientSocket : public Socket
{
private:
    struct sockaddr_in server_addr;
public:
    bool StringToBinary(char *ip, uint16_t port);
    bool ConnectSocket();
    void SendMessage(char *msg);
    void CloseSocket();
};
