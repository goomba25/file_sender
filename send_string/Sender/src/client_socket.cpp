#include "../include/client_socket.hpp"

bool ClientSocket::StringToBinary(char *ip, uint16_t port)
{
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // IPv4 & IPv6 바이너리 변경
    int value = inet_pton(AF_INET, ip, &server_addr.sin_addr);
    if (value <= 0)
    {
        std::cout << "inet_pton failed." << std::endl;
        return false;
    }
    else
    {
        std::cout << "inet_pton successed." << std::endl;
        return true;
    }
}

bool ClientSocket::ConnectSocket()
{
    int value = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (value < 0)
    {
        std::cout << "Connect failed." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Connect successed." << std::endl;
        return true;
    }
}

void ClientSocket::SendMessage(char *msg)
{
    send(sock, msg, strlen(msg), 0);
}

void ClientSocket::CloseSocket()
{
    close(sock);
}