#include "../include/server_socket.hpp"

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8000

int main(int argc, char *argv[])
{
    ServerSocket serv_socket;

    if (!serv_socket.BindSocket(PORT))
    {
        exit(1);
    }

    if (!serv_socket.ListenSocket(3))
    {
        exit(1);
    }
    std::cout << "Waiting for client connection..." << std::endl;

    while(1)
    {
        if (!serv_socket.AcceptSocket())
        {
            exit(1);
        }
        else
        {
            serv_socket.RecvFile();
            serv_socket.CloseAcceptSocket();
        }
    }

    serv_socket.CloseListenSocket();
}