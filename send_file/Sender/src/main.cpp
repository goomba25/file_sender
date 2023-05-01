#include "../include/client_socket.hpp"

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    ClientSocket client;
    if (!client.StringToBinary(SERVER_IP, PORT))
    {
        exit(1);
    }

    if (!client.ConnectSocket())
    {
        exit(1);
    }

    client.SendFile(argv[1]);
    client.CloseSocket();
    return 0;
}