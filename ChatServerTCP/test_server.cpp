#include "iostream"
#include "vector"
#include <cstring>

/// Thread libraries
#include "thread"
#include "mutex"
#include "atomic"

/// Connection libraries
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8000

std::mutex out_mutex, clients_mutex;
std::atomic<bool> server_running(true);

class Client{
public:
    int client_fd;
    std::string username;
    Client(int client_fd, std::string& username):
    client_fd {client_fd}, username{username}
    {}
};

std::vector<Client> clients;

void broadcast(int client_fd, std::string msg){
    for (auto client : clients){
        if (client.client_fd != client_fd){
            std::string new_msg = client.username + ": " + msg;
            send(client.client_fd, new_msg.c_str(), new_msg.length(), 0);
        }
    }
}

void handle_client(int client_fd){


    /// send
    std::string msg = "Hello from Server";
    send(client_fd, msg.c_str(), msg.length(), 0);

    // TODO: get username from user
    // TODO: Create a Client obj
    // TODO: add it to the client vector using the format below.
//    {
//        std::lock_guard<std::mutex> lock(clients_mutex);
//        clients.push_back(client_obj);
//    }

    /// recv
    while (server_running){
        char buffer [1024] = {0};
        recv(client_fd, buffer, sizeof(buffer), 0);
        broadcast(client_fd,buffer);
    }
    close(client_fd);
}

int main()
{
    /// create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1){
        std::cerr << "Socker failed" << std::endl;
        return -1;
    }

    /// define address
    sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    /// bind
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    /// listen
    if (listen(server_fd, 5) < 0){
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }

    while(server_running) {
        /// accept client
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "Client accept failed!" << std::endl;
            return -1;
        }

        std::thread client_thread(handle_client, client_fd);
        client_thread.detach();
    }

    std::cout << "Server shutting down." << std::endl;
    close(server_fd);
    return 0;

}
