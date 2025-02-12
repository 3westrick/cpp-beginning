#include <iostream>
#include <cstring>

/// Connection libraries
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

/// Thread libraries
#include <thread>
#include <mutex>
#include <atomic>

#define PORT 8000

std::mutex client_mutex;
std::mutex out_mutex;
std::atomic<bool> server_running(true);


void handle_receive(int client_fd){

    while (server_running){
        char buffer [1024] = {0};
        ssize_t bytes_receive = recv(client_fd, buffer, sizeof (buffer), 0);
        if (bytes_receive <= 0) {
            return;
        }

//        std::lock_guard<std::mutex> lock(out_mutex);
        std::cout << buffer << std::endl;
    }
    close(client_fd);
}

int main()
{
    /// create socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1){
        std::cerr << "Socker failed" << std::endl;
        return -1;
    }

    /// define address
    sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    /// connect (link bind in Server)
    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }


    char buffer [1024] = {0};
    while (true) {
        /// receive auth options
        memset(buffer, 0x00, sizeof(buffer));
        recv(client_fd, buffer, sizeof(buffer), 0);
        std::cout << buffer << std::endl;

        /// send e.g. /login admin 123
        std::string username;
        std::getline(std::cin, username);
        send(client_fd, username.c_str(), username.length(), 0);

        memset(buffer, 0x00, sizeof(buffer));
        recv(client_fd, buffer, sizeof(buffer), 0);
        std::string auth_log = buffer;

        if (auth_log == "1"){
            std::cout << "Login Successful";
            break;
        }else{
            std::cout << "Wrong Credentials";
        }
    }
    std::thread receive_thread(handle_receive, client_fd);
    receive_thread.detach();

    /// send
    while(server_running){
        std::string msg;
        std::getline(std::cin, msg);
        if (msg == "exit") break;
        send(client_fd, msg.c_str(), msg.length(), 0);
    }

    close(client_fd);

    return 0;
}