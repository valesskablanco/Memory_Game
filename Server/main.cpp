#include "server.hpp"
#include "dataStruct.hpp"

int main()
{
    //Server *Servidor = new Server();

    dataStruct *matrix = new dataStruct();

    matrix->createFile();
    matrix->getFCard(0, 0);
    matrix->getFCard(5, 1);
    matrix->getFCard(4, 3);
    matrix->getFCard(5, 6);
}
