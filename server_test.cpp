#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    //define socket file descriptor

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8888);   //hton func
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    //define sockaddr_in struct detail

    bind(sockfd,(sockaddr*)&server_addr,sizeof(server_addr));
    listen(sockfd,5);

    struct sockaddr_in client_addr;
    socklen_t client_len=sizeof(client_addr);
    int clientfd=accept(sockfd,(struct sockaddr *)&client_addr,&client_len);

    char buffer[256]={0};
    read(clientfd,buffer,255);
    std::cout<<buffer<<std::endl;

    close(clientfd);
    close(sockfd);

    return 0;
}