#include "client.hpp"

int main()
{
    Client *Cliente = new Client();
    while(true)
    {
        Cliente->Send();
        Cliente->Recieve();
    }
}
