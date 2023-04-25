#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    int pid;
    int signal;
    int kill_result = 0;

    while (kill_result == 0)
    {
        cout << "Insira o PID do processo: ";
        cin >> pid;

        cout << "Insira o ID do sinal a ser enviado: ";
        cin >> signal;

        kill_result = kill(pid, signal);
        

        if (kill_result == -1)
        {
            std::cerr << "Erro ao enviar o sinal " << signal << " para o processo " << pid << std::endl;
            return 1;
        }

        cout << "Sinal " << signal << " enviado com sucesso para o processo " << pid << "\n" << endl;
    }
    return 0;
}