#include "iostream"
#include "vector"
#include <cstring>
#include <unordered_map>
#include <fstream>

/// Thread libraries
#include "thread"
#include "mutex"
#include "atomic"

/// Connection libraries
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <string>
#include <ctime>
#include <sstream>

#define PORT 8000

std::mutex out_mutex, clients_mutex;
std::atomic<bool> server_running(true);

std::vector<int> clients;
std::unordered_map<int, std::string> client_names;

class Logger {
private:
    std::ofstream logFile;
    std::mutex log_mutex;
    static Logger* instance;
    static std::mutex instanceMutex;
    std::vector<std::string> chat_history;

    // Private constructor to prevent external instantiation
    Logger() {
        logFile.open("server.log", std::ios::app); // Append mode
        if (!logFile) {
            std::cerr << "Error opening log file!" << std::endl;
        }

        std::ifstream history("server.log");
        std::string line;
        while (std::getline(history, line)){
            chat_history.push_back(line);
        }
        history.close();
    }

    // Private destructor
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    // Disable copy and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        std::lock_guard<std::mutex> lock(instanceMutex);
        if (!instance) {
            instance = new Logger();
        }
        return *instance;
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(log_mutex);
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }


    // Get the stored chat history
    std::vector<std::string> getChatHistory() {
        std::lock_guard<std::mutex> lock(log_mutex);
        return chat_history;
    }
};

// Define static members
Logger* Logger::instance = nullptr;
std::mutex Logger::instanceMutex;



void broadcast(int client_fd, std::string msg){
    for (auto client : clients){
        if (client != client_fd){
            send(client, msg.c_str(), msg.length(), 0);
        }
    }
    Logger::getInstance().log(msg); // Use the Singleton Logger
}

void remove_client(int client_fd){
    std::lock_guard<std::mutex> lock(clients_mutex);

    std::string username = client_names[client_fd];
    client_names.erase(client_fd);
    clients.erase(std::remove(clients.begin(), clients.end(), client_fd), clients.end());

    close(client_fd);

    std::string exit_msg = "** " + username + " has left the chat **";
    std::cout << exit_msg;
    broadcast(client_fd, exit_msg);
}

void list_users(int client_fd) {
    std::lock_guard<std::mutex> lock(clients_mutex);

    std::string user_list = "Active users:\n";
    for (const auto& entry : client_names) {
        user_list += "- " + entry.second + "\n";
    }

    send(client_fd, user_list.c_str(), user_list.length(), 0);
}

void whisper_message(int sender_fd, const std::string& message) {
    // creates a stream (iss) from the input message string
    // allows extracting words individually, similar to reading input from std::cin
    std::istringstream iss(message);
    std::string command, target_username, whisper_msg;

    // extract the first two words from message:
    iss >> command >> target_username;  // extract command and target username
    std::getline(iss, whisper_msg);     // extract the remaining message

    if (whisper_msg.empty()) {
        std::string error_msg = "Usage: /whisper <username> <message>";
        send(sender_fd, error_msg.c_str(), error_msg.length(), 0);
        return;
    }

    int target_fd = -1;
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (const auto& entry : client_names) {
            if (entry.second == target_username) {
                target_fd = entry.first;
                break;
            }
        }
    }

    if (target_fd == -1) {
        std::string error_msg = "User " + target_username + " not found.";
        send(sender_fd, error_msg.c_str(), error_msg.length(), 0);
        return;
    }

    std::string sender_name = client_names[sender_fd];
    std::string whisper = "(Whisper from " + sender_name + "): " + whisper_msg;
    send(target_fd, whisper.c_str(), whisper.length(), 0);
}


// Check if user exists in `users.txt`
bool authenticate_user(const std::string& username, const std::string& password) {
    std::ifstream users_file("users.txt");
    std::string line;

    while (std::getline(users_file, line)) {
        std::istringstream iss(line);
        std::string stored_username, stored_password;
        iss >> stored_username >> stored_password;

        if (stored_username == username && stored_password == password) {
            return true;  // Successful login
        }
    }

    return false;  // Login failed
}

// Register a new user
bool register_user(const std::string& username, const std::string& password) {
    if (authenticate_user(username, password)) {
        return false;  // User already exists
    }

    std::ofstream users_file("users.txt", std::ios::app);
    users_file << username << " " << password << "\n";
    return true;
}

// Handle client login/register before chat
bool authenticate_client(int client_fd, std::string& username) {
    char buffer[1024];

    while (true) {
        std::string prompt = "Enter /login <username> <password> or /register <username> <password>: ";
        send(client_fd, prompt.c_str(), prompt.length(), 0);

        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) return false;  // Client disconnected

        std::istringstream iss(buffer);
        std::string command, user, pass;
        iss >> command >> user >> pass;

        if (command == "/login") {
            if (authenticate_user(user, pass)) {
                username = user;
                send(client_fd, "1", 1, 0);
                return true;
            } else {
                send(client_fd, "0", 1, 0);
            }
        } else if (command == "/register") {
            if (register_user(user, pass)) {
                username = user;
                send(client_fd, "Registration successful! You are now logged in.\n", 48, 0);
                return true;
            } else {
                send(client_fd, "Username already taken.\n", 25, 0);
            }
        } else {
            send(client_fd, "Invalid command.\n", 17, 0);
        }
    }
}

void handle_client(int client_fd){
    std::string username;

    if (!authenticate_client(client_fd, username)) {
        close(client_fd);
        return;  // Authentication failed
    }

    // get username from user

    std::vector<std::string> history = Logger::getInstance().getChatHistory();
    for(auto chat : history){
        chat += '\n';
        send(client_fd, chat.c_str(), chat.length(), 0);
    }

    std::string welcome_msg = "** " + username + " has joined the chat **";
    std::cout << welcome_msg;
    broadcast(client_fd, welcome_msg);

    // add it to the client
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        client_names[client_fd] = username;
    }

    /// recv
    while (server_running){
        char buffer [1024] = {0};
        ssize_t bytes_receive = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_receive <= 0){
            break;
        }

        std::string message = buffer;
        if (message == "/list") {
            list_users(client_fd);
        }else if (message.rfind("/whisper", 0) == 0){
            whisper_message(client_fd, message);
        }else if (message == "/exit"){
            break;
        }else {
            std::string chat_message = username + ": " + message;
            broadcast(client_fd, chat_message);
        }
    }

    // disconnect user
    remove_client(client_fd);
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

        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.push_back(client_fd);
        }

        std::thread client_thread(handle_client, client_fd);
        client_thread.detach();
    }

    std::cout << "Server shutting down." << std::endl;
    close(server_fd);
    return 0;

}
