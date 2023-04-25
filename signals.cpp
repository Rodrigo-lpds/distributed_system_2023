#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;  

int main()
{   
    int pid; 
    int signal;
    cout << "Enter process ID:";
    cin >> pid;
    
    cout << "Enter signal number:";
    cin >> signal;

    int result = kill(pid, signal);
    while (result == -1)
    {
        std::cerr << "Failed to send signal to process " << pid << std::endl;
        return 1;
    }
    return 0;
}