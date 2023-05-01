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

void ClientSocket::SendFile(char *file_name)
{
    std::ifstream input_stream;
    int file_size = 0;
    char buffer[BUF_SIZE] = {0};

    input_stream.open(file_name, std::ios::in | std::ios::binary);
    if (input_stream.fail())
    {
        std::cout << "Can't open " << file_name << std::endl;
        exit(1);
    }

    input_stream.seekg(0, std::ios::beg); // 파일 처음으로 이동

    send(sock, file_name, sizeof(file_name), 0);
    std::cout << "Send: " << file_name << std::endl;

    while (!input_stream.eof())
    {
        input_stream.read(buffer, BUF_SIZE);
        send(sock, buffer, BUF_SIZE, 0);
    }
    std::cout << "Transfer Complete" << std::endl;
}

void ClientSocket::CloseSocket()
{
    close(sock);
}