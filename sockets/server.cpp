#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

bool is_prime(int n)
{
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *response;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Error: socket failed" << std::endl;
        return 1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "Error: setsockopt failed" << std::endl;
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8081);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Error: bind failed" << std::endl;
        return 1;
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Error: listen failed" << std::endl;
        return 1;
    }

    std::cout << "Waiting for connections..." << std::endl;

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        std::cerr << "Error: accept failed" << std::endl;
        return 1;
    }

    std::cout << "Connection established" << std::endl;

    int valread;
    while ((valread = read(new_socket, buffer, 1024)) > 0)
    {
        std::cout << "Random number received: " << buffer << std::endl;
        int num = std::stoi(buffer);
        if (is_prime(num))
        {
            response = "The number is prime";
        }
        else
        {
            response = "The number is not prime";
        }
        send(new_socket, response, strlen(response), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    close(new_socket);
    return 0;
}
