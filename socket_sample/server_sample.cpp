#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 5555

int main(int argc, char *argv[])
{
    int server_sock, client_sock, client_len;
    char buffer[1024];

    if ((server_sock == socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 메세지 수신
    memset(buffer, 0, sizeof(buffer));
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);

    // 메세지 송신
    sprintf(buffer, "Hello, client!");
    send(client_sock, buffer, strlen(buffer), 0);

    close(client_sock);
    close(server_sock);

    return 0;
}