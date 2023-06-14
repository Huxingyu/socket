#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // 创建一个socket

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // 连接到服务器的8888端口
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);  // 连接到本地地址

    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));  // 连接到服务器

    const char* message = "Hello, Server!";
    write(sockfd, message, strlen(message));  // 发送消息到服务器

    close(sockfd);  // 关闭socket

    return 0;
}
