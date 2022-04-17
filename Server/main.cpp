#include "server.hpp"
#include "dataStruct.hpp"

int main()
{
    //Server *Servidor = new Server();

    dataStruct *pagedMemory = new dataStruct();

    pagedMemory->printMemory();
    pagedMemory->shuffle();
}
