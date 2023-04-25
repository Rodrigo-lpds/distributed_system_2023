#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Error: socket failed" << std::endl;
        return 1;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Error: setsockopt failed" << std::endl;
        return 1;
    }

    // Server address configuration
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8081);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        std::cerr << "Error: bind failed" << std::endl;
        return 1;
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Error: listen failed" << std::endl;
        return 1;
    }

    std::cout << "Waiting for connections..." << std::endl;

    // Accept incoming connections
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        std::cerr << "Error: accept failed" << std::endl;
        return 1;
    }

    std::cout << "Connection established" << std::endl;

    // Read incoming messages from the client
    int valread;
    while ((valread = read(new_socket, buffer, 1024)) > 0) {
        std::cout << "Message received: " << buffer << std::endl;
        // Send a response to the client
        send(new_socket, hello, strlen(hello), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    // Close the socket when done
    close(new_socket);
    return 0;
}
