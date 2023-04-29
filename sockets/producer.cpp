#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int n;
    int random_number;
    int times = 0;
    std::cout << "Type the number of times the program will run: ";
    std::cin >> n;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Error: failed to create socket" << std::endl;
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8081);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Error: failed to convert address" << std::endl;
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Error: failed to connect to server" << std::endl;
        return 1;
    }
    while (true)
    {
        if (times == n)
        {
            random_number = 0;
        }
        else
        {
            srand(time(nullptr));
            random_number = rand() % 100;
            times++;
        }
        std::string message = std::to_string(random_number);

        if (send(sock, message.c_str(), message.length(), 0) < 0)
        {
            std::cerr << "Error: failed to send message" << std::endl;
            return 1;
        }
        std::cout << "Number " << random_number << " sent to server" << std::endl;

        int valread = read(sock, buffer, 1024);
        if (valread < 0)
        {
            std::cerr << "Error: failed to receive response" << std::endl;
            return 1;
        }
        std::cout << "Server response: " << buffer << std::endl;
        sleep(1);
    }
    close(sock);
    return 0;
}
