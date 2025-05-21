#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio> // For perror
#include <cstdlib> // For EXIT_FAILURE

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    //define socket file descriptor
    if (sockfd < 0) {
        perror("Error opening socket in server_test");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8888);   //hton func
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    //define sockaddr_in struct detail

    if (bind(sockfd,(sockaddr*)&server_addr,sizeof(server_addr)) < 0) {
        perror("Error binding socket in server_test");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    if (listen(sockfd,5) < 0) {
        perror("Error listening on socket in server_test");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr;
    socklen_t client_len=sizeof(client_addr);
    int clientfd=accept(sockfd,(struct sockaddr *)&client_addr,&client_len);
    if (clientfd < 0) {
        perror("Error accepting client connection in server_test");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    char buffer[256]={0};
    ssize_t bytes_read = read(clientfd,buffer,255);
    if (bytes_read < 0) {
        perror("Error reading from client socket in server_test");
        close(clientfd);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    std::cout<<buffer<<std::endl;

    if (close(clientfd) < 0) {
        perror("Error closing client socket in server_test");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    if (close(sockfd) < 0) {
        perror("Error closing server socket in server_test");
        exit(EXIT_FAILURE);
    }

    return 0;
}