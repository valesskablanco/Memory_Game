#include "client.h"

int main(int argc, char const *argv[])
{
    Client *client = new Client();
    client->conection();
    return 0;
}