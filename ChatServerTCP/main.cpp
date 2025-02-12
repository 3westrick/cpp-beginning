#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <csignal>

#define PORT 8001

std::vector<int> clients;  // Store connected client sockets
std::mutex clients_mutex;  // Mutex for thread safety
std::atomic<bool> server_running(true);  // Track server state

// Signal handler for graceful shutdown
void signal_handler(int signum) {
    std::cout << "\nShutting down server..." << std::endl;
    server_running = false;
    close(STDIN_FILENO);  // Close standard input to break accept() loop
}

void broadcast(int client_fd, std::string& message){
    std::lock_guard<std::mutex> lock(clients_mutex);
    for(auto other_client_fd: clients){
        if (client_fd != other_client_fd){
            send(other_client_fd, message.c_str(), message.length(), 0);
        }
    }
}

void handle_client(int client_fd) {
    std::string join_msg = "User Joined: #" + std::to_string(client_fd);
    broadcast(client_fd, join_msg);
    char buffer[1024];
    while(server_running){
        memset(buffer, 0, sizeof(buffer));
        // Receive data from the client
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            std::cout << "Client disconnected." << std::endl;
            break;
        }
        std::string message = "Client " + std::to_string(client_fd) + ": " + buffer;
        std::cout << message;

        broadcast(client_fd, message);
    }

    // Close client socket
    close(client_fd);
}


int main()
{
    // Register SIGINT (Ctrl+C) handler
//    signal(SIGINT, signal_handler);

    // Create a TCP socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) throw std::runtime_error("Socket creation failed!");

    // Define server address
    sockaddr_in server_addr {};
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to an IP & port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(server_fd);
        throw std::runtime_error("Bind failed!");
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        close(server_fd);
        return -1;
    }
    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    // accept
    while (server_running){
        sockaddr_in client_addr {};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (client_fd < 0) {
            if (server_running) {
                std::cerr << "Client accept failed!" << std::endl;
            }
            continue;
        }
        std::cout << "New client connected: " << client_fd << std::endl;
        clients.push_back(client_fd);

        std::thread client_thread(handle_client, client_fd);
        client_thread.detach();

    }

    close(server_fd);
    std::cout << "Server shut down gracefully!" << std::endl;

    return 0;
}