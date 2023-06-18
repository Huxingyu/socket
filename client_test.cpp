#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8888);
    //server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    inet_pton(AF_INET,"127.0.0.2",&server_addr.sin_addr);

    connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    
    const char* message="gogogo";
    write(sockfd,message,strlen(message));

    close(sockfd);
    return 0;
}