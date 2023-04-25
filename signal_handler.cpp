#include <csignal>
#include <iostream>
using namespace std;

void signal_handler1(int signal_num)
{
    cout << "Received signal " << signal_num << ", shutting down gracefully..." << endl;
    exit(signal_num);
}

void signal_handler2(int signal_num)
{
    cout << "Received signal " << signal_num << ", ignoring signal..." << endl;
}

void signal_handler3(int signal_num)
{
    cout << "Received signal " << signal_num << ", doing some cleanup..." << endl;
}

int main()
{
    int wait_type;

    signal(SIGINT, signal_handler1);
    signal(SIGUSR1, signal_handler2);
    signal(SIGUSR2, signal_handler3);

    cout << "Type 0 for busy waits or type 1 for block waits." << endl;
    cin >> wait_type;

    if (wait_type == 0)
    {
        cout << "Busy wait..." << endl;
        while (true)
        {
            sleep(1); // Wait for 1 second
        }
    }
    else if (wait_type == 1)
    {
        cout << "Block wait..." << endl;
        while (true)
        {
            pause();
        }
    }

    return 0;
}
