#include <iostream>
#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int server_sock, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE] = {0};

    // Create socket descriptor
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed.");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
}