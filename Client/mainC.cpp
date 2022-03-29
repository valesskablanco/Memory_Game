#include "client.hpp"

int main()
{
    Client *Cliente = new Client();

    Cliente->Send();
    Cliente->Recieve();
    Cliente->CloseSocket();
}
