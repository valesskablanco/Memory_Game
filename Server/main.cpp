#include "server.hpp"
#include "dataStruct.hpp"

int main()
{
    //Server *Servidor = new Server();

    dataStruct *matrix = new dataStruct();

    matrix->createFile();
    matrix->createPagedMemory();
}
