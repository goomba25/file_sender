#include "../include/server_socket.hpp"

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8000

void RecvFile(int socket);

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
            std::thread thread1 = std::thread(RecvFile, serv_socket.GetSocket());
            thread1.detach();
        }
    }

    serv_socket.CloseListenSocket();
}

void RecvFile(int socket)
{
    struct Packet packet;
    char file_name[200] = {0,};
    recv(socket, file_name, 200, 0);

    std::ofstream output_stream(file_name, std::ios::out | std::ios::binary);
    std::cout << "Recv: " << file_name << std::endl;
    int total = 0;
    do
    {
        recv(socket, (struct Packet*)&packet, sizeof(packet), 0);
        int buffer_size = sizeof(packet.buffer);
        output_stream.write(packet.buffer, buffer_size);
        total += buffer_size;
        std::cout << file_name << " : " << total << "/" << packet.size << std::endl;
    }
    while(total < packet.size);

    output_stream.close();
    std::cout << "Server Transfer Complete : " << file_name << std::endl;
    close(socket);
}