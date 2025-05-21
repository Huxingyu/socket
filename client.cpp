#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <cstdio> // For perror
#include <cstdlib> // For EXIT_FAILURE

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // 创建一个socket
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // 连接到服务器的8888端口
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {  // 连接到本地地址
        perror("Invalid address/ Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {  // 连接到服务器
        perror("Error connecting to server");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    const char* message = "Hello, Server!";
    ssize_t bytes_written = write(sockfd, message, strlen(message));  // 发送消息到服务器
    if (bytes_written < 0) {
        perror("Error writing to socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (close(sockfd) < 0) {  // 关闭socket
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    }
    //test
    return 0;
}