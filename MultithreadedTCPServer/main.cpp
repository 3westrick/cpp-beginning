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

#define PORT 8000

std::vector<std::thread> client_threads;  // Store client threads
std::mutex thread_mutex;  // Mutex for thread safety
std::atomic<bool> server_running(true);  // Track server state

// Signal handler for graceful shutdown
void signal_handler(int signum) {
    std::cout << "\nShutting down server..." << std::endl;
    server_running = false;
    close(STDIN_FILENO);  // Close standard input to break accept() loop
}

int create_tcp_socket(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) throw std::runtime_error("Socket creation failed!");
    return server_fd;
}

sockaddr_in define_server_address(){
    sockaddr_in server_addr {};
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    return server_addr;
}

void bind_socket(auto server_fd, auto server_addr){
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(server_fd);
        throw std::runtime_error("Bind failed!");
    }
}

void handle_client(int client_fd) {
    char buffer[1024] = {0};

    // Receive data from the client
    recv(client_fd, buffer, sizeof(buffer), 0);
    std::cout << "Received from client: " << buffer << std::endl;

    // Send a response
    const char* response = "Hello from Server!";
    send(client_fd, response, strlen(response), 0);
//    send(client_fd, "Hello from Server!", 18, 0);

    // Close client socket
    close(client_fd);
}

int main()
{
    // Register SIGINT (Ctrl+C) handler
    signal(SIGINT, signal_handler);

    /// <h3>Implementing a Multithreaded TCP Server</h3>
    // Create a TCP socket
    int server_fd = create_tcp_socket();

    // Define server address
    sockaddr_in server_addr = define_server_address();

    // Bind the socket to an IP & port
    bind_socket(server_fd, server_addr);

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Listen failed!" << std::endl;
        close(server_fd);
        return -1;
    }
    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    while (server_running) {
        sockaddr_in client_addr {};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (!server_running) break;
        if (client_fd < 0) {
            std::cerr << "Client accept failed!" << std::endl;
            continue;
        }
        std::cout << "Client connected! " << client_fd << std::endl;

        std::lock_guard<std::mutex> lock(thread_mutex);
        client_threads.emplace_back(handle_client, client_fd);
        //std::thread new_thread(handle_client, client_fd);
        //client_threads.push_back(std::move(new_thread));  // Move thread into vector

    }
    
    std::cout << "Waiting for active client threads to finish..." << std::endl;
    for (auto& t : client_threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    close(server_fd);
    std::cout << "Server shut down gracefully!" << std::endl;

    return 0;
}