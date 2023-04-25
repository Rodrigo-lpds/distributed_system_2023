#include <unistd.h>
#include <iostream>
#include <string>

void calculate_prime(int n){
    for (int i = 2; i < n; i++){
        if (n % i == 0){
            std::cout << "Not prime" << std::endl;
            return;
        }
    }
    std::cout << "Prime" << std::endl;
}

int main() {
    int pipefd[2];
    char buffer[1024];
    int n = 1;


    if (pipe(pipefd) < 0) {
        std::cerr << "Error: failed to create pipe" << std::endl;
        return 1;
    }
    for (int i = 0; i < 100; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            std::cerr << "Error: failed to fork" << std::endl;
            return 1;
        } else if (pid == 0) {
            // Child process. aka the consumer
            close(pipefd[1]); // Close unused write end
            read(pipefd[0], buffer, sizeof(buffer));
            //n += std::stoi(buffer); 
            //calculate_prime(n);
            std::cout << "Child received message: " << buffer << std::endl;
            close(pipefd[0]); // Close read end
            return 0;
        } else {
            // Parent process aka the producer
            close(pipefd[0]); // Close unused read end
            //std::string message = "Hello from parent";
            srand(time(0));
            std::string message = std::to_string(rand() % 100);
            write(pipefd[1], message.c_str(), message.size());
            close(pipefd[1]); // Close write end
        }
    }
    return 0;
}
