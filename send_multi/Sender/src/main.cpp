#include "../include/client_socket.hpp"

#include <iostream>
#include <thread>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define BUF_SIZE 1024

void open_socket(char *file_name);

int main(int argc, char *argv[])
{
    std::thread thread1 = std::thread(open_socket, argv[1]);
    std::thread thread2 = std::thread(open_socket, argv[2]);
    thread1.join();
    thread2.join();
    return 0;
}

void open_socket(char *file_name)
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

    client.SendFile(file_name);
    client.CloseSocket();
}