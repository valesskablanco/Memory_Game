#include "server.hpp"

int main()
{
    Server *Servidor = new Server();
    while(true)
    {
        Servidor->Recieve();
        Servidor->Send();
    }
}
