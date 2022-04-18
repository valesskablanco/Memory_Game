#include "client.hpp"

using namespace std;

Client::Client()
{

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(server_ip);
    serverAddress.sin_port = htons(PORT);

    char *buffer = new char[1024];

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientsocket < 0)
    {
        cout << "\n Socket creation error \n"
             << endl;
    }
    else
    {
        cout << "\n Socket connection successful \n"
             << endl;

        if (connect(clientsocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            cout << "\n Connection failed \n"
                 << endl;
        }
        else
        {
            cout << "\n Connection to server succesfully \n"
                 << endl;
        }
    }
}

/**
 * 1 byte operacion a realizar:
 *  - ejemplo: obtener dimensiones del mazo
 *      - Envio 0 (1 byte)
 *      - Recibo 2 byte: primer byte son las filas y segunda byte son las columnas
 *      - Server handler:
 *          msg[0] == '0'?
 *          request_handler.send_dims(buffer); -> responder inmediatamente
 *          char* response/string msg = request_handler.handle_dims(buffer); -> te da la respuesta
 *          request_handler.handle_dims(buffer, response); -> te da la respuesta en char response[]
 *          In request handle:
 *              int i = (int) msg[1]
 *              int j = (int) msg[2]
 *  - 0 obtener carta
 *      - Envio 0 - i - j (3 byte)
 *      - Recibo base 64 de la carta
 *  - 1 comparar cartas
 *      - Envio 1 - i1 - j1 - i2 - j2 (5 bytes)
 *      - Recibo true o false (0 o 1) (1 byte)
 *  - 2 verificar si esta en memoria
 *      - Envio 2 - i - j (3 bytes)
 *      - Recibo true o false (0 o 1) (1 byte)
 */

//

void Client::requestHandler(char Request[1024])
{
    // First, sending the request
    this->buffer = Request;
    write(clientsocket, this->buffer, strlen(this->buffer));
    //memset(buffer, 0, sizeof(buffer));
    cout << "\n Message sent \n"
         << endl;

    // Reading the server's response
    char operation = this->buffer[0];

    if (operation == "0")
    {
        read(clientsocket, this->buffer, sizeof(this->buffer));
        //return base 64
    }
    else if (operation == "1")
    {
        read(clientsocket, this->buffer, sizeof(this->buffer));
        //return 0 or 1
    }
    else if (operation == "2")
    {
        read(clientsocket, this->buffer, sizeof(this->buffer));
        //return 0 or 1
    }
    
}

void Client::closeSocket()
{
    close(clientsocket);
    cout << "Socket closed" << endl;
}

void Client::decode()
{
    //decodificar la imagen en base 64
}
