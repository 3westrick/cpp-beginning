#include <iostream> // For input-output
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in (internet address structure)
#include <unistd.h>    // For close() function
#include <cstring>  // For memset()

#define PORT 8000  // Server port

int main()
{
     // creating socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_fd){
        std::cerr << "Socket Creation Failed" << std::endl;
        return -1;
    }

    // define address
    sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // bind
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        std::cerr << "Bind Failed" << std::endl;
        close(server_fd);
        return -1;
    }

    // listen
    if (listen(server_fd, 5) < 0){
        std::cerr << "Listen Failed" << std::endl;
        close(server_fd);
        return -1;
    }
    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    // Accept a client connection
    sockaddr_in client_addr {};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        std::cerr << "Client accept failed!" << std::endl;
        close(server_fd);
        return -1;
    }

    std::cout << "Client connected!" << std::endl;

    // Receive data from the client
    char buffer[1024] = {0};

//    recv(client_fd, buffer, sizeof(buffer), 0);
//    std::cout << "Client: " << buffer << std::endl;

    //Send a response to the client

    std::string res ="";
    std::cin >> res;

    std::cout << res << std::endl;
    std::cout << &res << std::endl;
    send(client_fd, &res, size(res), 0);

    return 0;
}