#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <atomic>

#define PORT 8000

std::mutex client_mutex;
std::atomic<bool> server_running(true);

void receive_messages(int client_fd)
{
    char buffer[1024];

    while(server_running){
        memset(buffer, 0, sizeof(buffer));

        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            std::cout << "Disconnected from server." << std::endl;
            break;
        }
        std::cout << buffer;
    }
}


int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    sockaddr_in server_addr {};
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

    // Receive response from server
    std::lock_guard<std::mutex> lock(client_mutex);

    std::thread recv_thread(receive_messages, client_fd);
    recv_thread.detach();

    std::string message;
    while (true) {
        std::getline(std::cin, message);
        if (message == "exit") break;
        send(client_fd, message.c_str(), message.length(), 0);
    }

    close(client_fd);
    return 0;
}
