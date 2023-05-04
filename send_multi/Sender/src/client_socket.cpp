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
    std::cout << "Start" << std::endl;
    std::ifstream input_stream;
    struct Packet packet;

    input_stream.open(file_name, std::ios::in | std::ios::binary);
    if (input_stream.fail())
    {
        std::cout << "Can't open " << file_name << std::endl;
        exit(1);
    }

    input_stream.seekg(0, std::ios::end);
    packet.size = input_stream.tellg();
    input_stream.seekg(0, std::ios::beg);

    char file_name_packet[200] = {0,};
    strcpy(file_name_packet, file_name);

    send(sock, file_name_packet, 200, 0);
    std::cout << "Send: " << file_name_packet << std::endl;
    int total = 0;
    while (!input_stream.eof())
    {
        input_stream.read(packet.buffer, BUF_SIZE);
        int buffer_size = sizeof(packet.buffer);
        send(sock, (struct Packet*)&packet, sizeof(packet), 0);
        total += buffer_size;
        std::cout << file_name << " : " << total << "/" << packet.size << std::endl;
    }
    std::cout << "Transfer Complete : " << file_name_packet << std::endl;
}

void ClientSocket::CloseSocket()
{
    close(sock);
}