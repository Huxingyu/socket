#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    //define socket file descriptor

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8888);   //hton func
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    //define sockaddr_in struct detail

    bind(sockfd,(sockaddr*)&server_addr,sizeof(server_addr));
    

    return 0;
}

