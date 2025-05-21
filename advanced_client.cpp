#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <cstdio> // For perror
#include <cstdlib> // For EXIT_FAILURE
#include <iostream> // For std::cout, std::cerr
#include <string>   // For std::string, std::stoi

int main(int argc, char *argv[]){
    if (argc != 3) {
        std::cerr << "Usage: ./advanced_client <server_ip> <port>" << std::endl;
        exit(EXIT_FAILURE);
    }

    const char* server_ip = argv[1];
    int port_num;
    try {
        port_num = std::stoi(argv[2]);
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid port number: " << argv[2] << std::endl;
        exit(EXIT_FAILURE);
    } catch (const std::out_of_range& oor) {
        std::cerr << "Port number out of range: " << argv[2] << std::endl;
        exit(EXIT_FAILURE);
    }

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0) {
        perror("Error opening socket in advanced_client");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(static_cast<short>(port_num)); // Use provided port
    
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) { // Use provided IP
        perror("Invalid address/ Address not supported in advanced_client");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0) {
        perror("Error connecting to server in advanced_client");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    const char* message="gogogo";
    ssize_t bytes_written = write(sockfd,message,strlen(message));
    if (bytes_written < 0) {
        perror("Error writing to socket in advanced_client");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (close(sockfd) < 0) {
        perror("Error closing socket in advanced_client");
        exit(EXIT_FAILURE);
    }
    std::cout << "Message sent to " << server_ip << ":" << port_num << std::endl;
    return 0;
}