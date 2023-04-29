#include <unistd.h>
#include <iostream>
#include <string>

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
    int pipefd[2];
    char buffer[1024];
    int n;

    std::cout << "Type the number of times the program will run: ";
    std::cin >> n;

    for (int i = 0; i < n; i++) // Executar 5 vezes
    {
        if (pipe(pipefd) < 0)
        {
            std::cerr << "Error: failed to create pipe" << std::endl;
            return 1;
        }
        pid_t pid = fork();
        if (pid < 0)
        {
            std::cerr << "Error: failed to fork" << std::endl;
            return 1;
        }
        else if (pid == 0)
        {
            // Consumer
            close(pipefd[1]);
            read(pipefd[0], buffer, sizeof(buffer));
            close(pipefd[0]);

            int num = std::stoi(buffer);
            std::string response;
            if (is_prime(num))
            {
                response = " is prime";
            }
            else
            {
                response = " is not prime";
            }

            std::cout << "The number " << buffer << response << std::endl;
            return 0;
        }
        else
        {
            // Producer
            close(pipefd[0]);
            srand(time(0));
            int num = rand() % 100;
            std::string message = std::to_string(num);
            sleep(1);
            write(pipefd[1], message.c_str(), message.size());
            close(pipefd[1]);
        }
    }
    return 0;
}
