#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5555

int main(int argc, char* argv[]) {
    int sock;
    char buffer[1024];

    if ((sock == socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 메세지 송신
    sprintf(buffer, "Hello, server!");
    send(sock, buffer, strlen(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Received from server: %s\n", buffer);

    close(sock);

    return 0;
}