#include "client.hpp"
#include "interface.hpp"

int main()
{
    Interface *GUI = new Interface();
    Client *Cliente = new Client();

    Cliente->Send();
    Cliente->CloseSocket();
}
