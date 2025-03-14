#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 8000

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        close(client_fd);
        return -1;
    }

    std::cout << "Connected to server!" << std::endl;

    // Send message to server
    const char* message = "Hello, Server!";
    send(client_fd, message, strlen(message), 0);

    // Receive response from server
    char buffer[1024] = {0};
    recv(client_fd, buffer, sizeof(buffer), 0);
    std::cout << "Received from server: " << buffer << std::endl;

    close(client_fd);
    return 0;
}
