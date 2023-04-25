#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Error: failed to create socket" << std::endl;
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8081);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Error: failed to convert address" << std::endl;
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error: failed to connect to server" << std::endl;
        return 1;
    }

    // Send a message to the server
    std::string message = "Hello from client";
    if (send(sock, message.c_str(), message.length(), 0) < 0) {
        std::cerr << "Error: failed to send message" << std::endl;
        return 1;
    }
    std::cout << "Message sent to server" << std::endl;

    // Receive a response from the server
    int valread = read(sock, buffer, 1024);
    if (valread < 0) {
        std::cerr << "Error: failed to receive response" << std::endl;
        return 1;
    }
    std::cout << "Server response: " << buffer << std::endl;

    close(sock);
    return 0;
}
