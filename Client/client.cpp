#include "client.hpp"

using namespace std;

Client::Client()
{

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(server_ip);
    serverAddress.sin_port = htons(PORT);

    char *buffer = new char[BUFFER_SIZE];

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

            char Request[BUFFER_SIZE] = "012\0";
            this->send(Request);
            this->requestHandler();
            this->closeSocket();
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
 *      - Recibo true o false (0 o 1) (1 byte)
 *      - Recibo binario de la carta (n bytes)
 *  - 1 comparar cartas
 *      - Envio 1 - i1 - j1 - i2 - j2 (5 bytes)
 *      - Recibo true o false (0 o 1) (1 byte)
 */

//

void Client::requestHandler()
{
    // Reading the server's response
    char operation = this->buffer[0];
    read(clientsocket, this->buffer, sizeof(this->buffer));

    if (operation == '0')
    {
        // return base 64
    }
    else if (operation == '1')
    {
        // return 0 or 1
    }

    cout << this->buffer << endl;
}

void Client::send(char Request[BUFFER_SIZE])
{
    strcpy(this->buffer, Request);
    write(clientsocket, Request, strlen(Request));
}

void Client::closeSocket()
{
    close(clientsocket);
    cout << "Socket closed" << endl;
}


void Client::decodeImg(string img)
{
    ofstream image("rebuild.png", ios::out | ios::trunc);
    
    while (img.size() > 0)
    {
        ch = img.substr(0, 1).c_str()[0];
        image.put(ch);
        img = img.substr(1);
    }

    image.clear();
}
