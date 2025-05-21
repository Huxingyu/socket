#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
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
    server_addr.sin_port = htons(8888);  // 监听8888端口
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 任何地址都可以连接

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {  // 绑定地址和端口
        perror("Error binding socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {  // 开始监听, backlog set to 5
        perror("Error listening on socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port 8888..." << std::endl;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);  // 接受客户端的连接
        if (clientfd < 0) {
            perror("Error on accept");
            // Continue to accept other clients
            continue; 
        }

        // Optional: Print client connection information (can be added later)
        // char client_ip[INET_ADDRSTRLEN];
        // inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        // std::cout << "Accepted connection from " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;

        char buffer[256] = {0};
        ssize_t bytes_read = read(clientfd, buffer, 255);  // 读取客户端发送的消息
        if (bytes_read < 0) {
            perror("Error reading from client socket");
            // Don't exit the server, just close this client's connection
        } else if (bytes_read == 0) {
            std::cout << "Client disconnected before sending data." << std::endl;
        } else {
            std::cout << "Message from client: " << buffer << std::endl;  // 打印消息
        }

        if (close(clientfd) < 0) {  // 关闭客户端的连接
            perror("Error closing client socket");
            // This error is for a specific client, server should continue
        }
        std::cout << "Client disconnected. Waiting for new connection..." << std::endl;
    }

    // The following lines are now effectively unreachable in a while(true) loop.
    // For a real server, a signal handler would be used to trigger shutdown.
    if (close(sockfd) < 0) {  // 关闭服务器的socket
        perror("Error closing server socket");
        // If this fails, not much else to do here as we'd be exiting anyway
        // in a real shutdown sequence.
        exit(EXIT_FAILURE); 
    }

    return 0; // Unreachable
}
