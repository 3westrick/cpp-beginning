/// Networking in C++ is done using sockets, which enable sending and receiving data over a network.<br>
/// ✔️ Uses TCP/IP and UDP protocols<br>
/// ✔️ Enables server-client communication<br>
/// ✔️ Requires <sys/socket.h> (Linux) or <winsock2.h> (Windows)

#include <iostream> // For input-output

///Creating a TCP Server (Linux)
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in (internet address structure)
#include <unistd.h>    // For close() function
#include <cstring>  // For memset()

#define PORT 8000  // Server port

int main()
{
    /// <h3>Create a Server Socket</h3>
    /// AF_INET → Use IPv4 | SOCK_STREAM → Use TCP (not UDP) | 0 → Default protocol (TCP)
    /// if socket() fails, it returns -1
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }


    /// Define the Server Address
    sockaddr_in server_addr{};
    memset(&server_addr, 0, sizeof(server_addr));  // Clear structure
    server_addr.sin_family = AF_INET;  // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any IP
    server_addr.sin_port = htons(PORT);  // Convert port 8000 to network byte order

    /// Bind the Server Socket to an IP and Port.<br>
    /// bind() connects the socket to IP + Port.<br>
    /// If bind() fails, the port might be already in use.
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        close(server_fd);
        return -1;
    }

    /// Listen for Incoming Connections.<br>
    /// Starts listening for incoming connections.<br>
    /// The 5 means the server queues up to 5 clients before rejecting new ones.
//    listen(server_fd, 5);
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        close(server_fd);
        return -1;
    }
    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    /// Accept a Client Connection.<br>
    /// accept() waits for a client to connect.<br>
    /// If successful, client_fd stores the client's socket descriptor.
    sockaddr_in client_addr {};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        std::cerr << "Client accept failed!" << std::endl;
        close(server_fd);
        return -1;
    }

//    int client_fd = accept(server_fd, nullptr, nullptr);
//    if (client_fd < 0) {
//        std::cerr << "Client accept failed!" << std::endl;
//        return -1;
//    }


    /// Communicate with the Client<br>
    /// At this point, the client is connected to the server.<br>
    /// You can now use send() and recv() to exchange data.
    std::cout << "Client connected!" << std::endl;

    /// Receive data from the client
    char buffer[1024] = {0};
    recv(client_fd, buffer, sizeof(buffer), 0);
    std::cout << "Received from client: " << buffer << std::endl;

    /// Send a response to the client
    const char* response = "Hello from Server!";
    send(client_fd, response, strlen(response), 0);

    /// Close connections
    close(client_fd);
    close(server_fd);


    return 0;
}