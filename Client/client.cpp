#include "client.hpp"

using namespace std;

/**
 * @brief Construct a Client object
 * Creates the client socket
 * Connects the client to the server
 */
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
 * @brief Handles the Server response
 * @return char
 */
char Client::requestHandler()
{
    // Reading the server's response
    char operation = this->buffer[0];
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
    return result;
}

/**
 * @brief sends a buffer through the socket and handles the response
 * @param Request a char array with the request
 * @return char
 */
char Client::send(char Request[BUFFER_SIZE])
{
    strcpy(this->buffer, Request);
    write(clientsocket, Request, strlen(Request));
    return this->requestHandler();
}

/**
 * @brief closes the client socket
 */
void Client::closeSocket()
{
    close(clientsocket);
    cout << "Socket closed" << endl;
}

/**
 * @brief decodes the image from binary and 
 * rebuilds it
 */
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
