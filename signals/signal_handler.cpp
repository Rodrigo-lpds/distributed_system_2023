#include <csignal>
#include <iostream>
using namespace std;

void signal_handler_interrupt(int signal_num)
{
    cout << "Sinal de Interrupt recebido " << signal_num << endl;
    exit(signal_num);
}

void signal_handler_floating_point(int signal_num)
{
    cout << "Sinal de Floating Point recebido " << signal_num << endl;
}

void signal_handler_segmentation_fault(int signal_num)
{
    cout << "Sinal de Segmentation Fault recebido" << signal_num << endl;
}

int main()
{
    signal(SIGINT, signal_handler_interrupt);
    signal(SIGFPE, signal_handler_floating_point);
    signal(SIGSEGV, signal_handler_segmentation_fault);

    int wait_type;
    cout << "Digite 0 para Busy Wait e Digite 1 para Block Wait" << endl;
    cin >> wait_type;

    if (wait_type == 0)
    {
        cout << "Busy wait..." << endl;
        while (true)
        {
            sleep(1);
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
