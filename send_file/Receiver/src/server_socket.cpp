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

void ServerSocket::RecvFile()
{
    char file_name[BUF_SIZE];
    memset(file_name, 0, BUF_SIZE);
    recv(client_sock, file_name, BUF_SIZE, 0);

    // strcat(path, file_name);
    std::ofstream output_stream(file_name, std::ios::out | std::ios::binary);
    std::cout << "이름: " << file_name << std::endl;
    int size = BUF_SIZE;
    while (size != 0)
    {
        memset(buffer, 0, sizeof(buffer));
        size = recv(client_sock, buffer, sizeof(buffer), 0);
        output_stream.write(buffer, sizeof(buffer));
    }

    output_stream.close();
    std::cout << "Server Transfer Complete." << std::endl;
}

void ServerSocket::CloseListenSocket()
{
    close(sock);
}

void ServerSocket::CloseAcceptSocket()
{
    close(client_sock);
}