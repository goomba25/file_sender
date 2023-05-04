#include "../include/server_socket.hpp"

bool ServerSocket::BindSocket(uint16_t port)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int value = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (value < 0) {
        std::cout << "Bind failed." << std::endl;
        return false;
    }
    else {
        return true;
    }
}

bool ServerSocket::ListenSocket(int count)
{
    int value = listen(sock, count);
    if (value < 0) {
        std::cout << "Listen failed." << std::endl;
        return false;
    }
    else {
        return true;
    }
}

bool ServerSocket::AcceptSocket()
{
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(addr);
    client_sock = accept(sock, (struct sockaddr *)&addr, &addr_size);

    if (client_sock < 0) {
        std::cout << "Accept failed." << std::endl;
        return false;
    }
    else {
        std::cout << "Accept Successed." << std::endl;
        return true;
    }
}

void ServerSocket::CloseListenSocket()
{
    close(sock);
}

int ServerSocket::GetSocket()
{
    return client_sock;
}