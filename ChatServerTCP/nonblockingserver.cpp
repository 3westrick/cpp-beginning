//
// Created by arad afraz on 2/11/25.
//
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <csignal>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

std::atomic<bool> running(true);
int server_fd = -1; // Global socket for cleanup in signal handler

void signalHandler(int signum) {
    std::cout << "\nStopping server...\n";
    running = false;
    if (server_fd != -1) close(server_fd); // Close the server socket
}

int main() {
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket to non-blocking mode
    fcntl(server_fd, F_SETFL, O_NONBLOCK);

    // Bind to a port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8001);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Register signal handler for Ctrl+C
    signal(SIGINT, signalHandler);

    std::cout << "Server started. Press Ctrl+C to stop.\n";

    fd_set read_fds;
    struct timeval timeout;

    while (running) {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);

        timeout.tv_sec = 1;  // 1 second timeout
        timeout.tv_usec = 0;

        // Use select() to check if there's a connection request
        int activity = select(server_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (activity < 0 && running) {
            perror("Select error");
            break;
        }

        if (activity > 0 && FD_ISSET(server_fd, &read_fds)) {
            int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
            if (new_socket < 0) {
                perror("Accept failed");
                continue;
            }
            std::cout << "New client connected!\n";
            close(new_socket);
        }
    }

    // Cleanup
    close(server_fd);
    std::cout << "Server stopped.\n";

    return 0;
}
