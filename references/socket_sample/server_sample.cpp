#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 5555

int main(int argc, char* argv[]) {
    int server_sock, client_sock;
    socklen_t client_len;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];

    // 소켓 생성
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // 소켓에 주소 할당
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 클라이언트 연결 대기
    if (listen(server_sock, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for client connection...\n");

    // 클라이언트 연결 수락
    client_len = sizeof(client_addr);
    if ((client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");

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