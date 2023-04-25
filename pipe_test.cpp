#include <iostream>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[1024];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        std::cerr << "Error: failed to create pipe" << std::endl;
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        pid = fork();

        if (pid < 0) {
            std::cerr << "Error: failed to fork" << std::endl;
            return 1;
        } else if (pid == 0) {
            // Child process
            close(pipefd[1]); // Close unused write end
            read(pipefd[0], buffer, sizeof(buffer));
            std::cout << "Child received message: " << buffer << std::endl;
            close(pipefd[0]); // Close read end
            return 0;
        } else {
            // Parent process
            close(pipefd[0]); // Close unused read end
            std::string message = "Hello from parent";
            write(pipefd[1], message.c_str(), message.size());
            close(pipefd[1]); // Close write end
        }
    }

    return 0;
}
