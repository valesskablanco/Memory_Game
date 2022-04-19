#include "client.hpp"

using namespace std;

Client::Client()
{

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(server_ip);
    serverAddress.sin_port = htons(PORT);

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
 *
 *  - 0 obtener carta
 *      - Envio 0 - i - j (3 byte)
 *      - Recibo true o false (0 o 1) (1 byte)
 *      - Recibo tamano de la imagen codificada
 *      - Recibo binario de la carta (n bytes)
 *  - 1 comparar cartas
 *      - Envio 1 - i1 - j1 - i2 - j2 (5 bytes)
 *      - Recibo true o false (0 o 1) (1 byte)
 */

//

char Client::requestHandler()
{
    // Reading the server's response
    char operation = this->buffer[0];
    cout << "Estoy leyendo" << endl;
    memset(this->buffer, 0, sizeof(this->buffer));
    read(clientsocket, this->buffer, sizeof(this->buffer));

    char result;

    if (operation == '0')
    {
        result = this->buffer[0];
        int img_size = (int)this->buffer[1] * 100 + (int)this->buffer[2] * 10 + (int)this->buffer[3];

        decodeImg(img_size);

        return this->buffer[0];
    }
    else if (operation == '1')
    {
        result = this->buffer[0];
    }
    cout << "Termine" << endl;
    return result;
}

char Client::send(char Request[BUFFER_SIZE])
{
    strcpy(this->buffer, Request);
    write(clientsocket, Request, strlen(Request));
    return this->requestHandler();
}

void Client::closeSocket()
{
    close(clientsocket);
    cout << "Socket closed" << endl;
}


void Client::decodeImg(int img_size)
{
    ofstream image("./temp/rebuild.png", ios::out | ios::trunc);

    for (int i = 0; i < img_size; ++i)
    {
        char ch = this->buffer[i + 4]; // img.substr(0, 1).c_str()[0];
        image.put(ch);
    }
    image.clear();
}
