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

void Client::send()
{

    cout << "Write your message: ";
    cin >> this->buffer;
    write(clientsocket, buffer, strlen(buffer));
    memset(buffer, 0, sizeof(buffer));
    cout << "\n Message sent \n"
         << endl;
}

void Client::closeSocket()
{
    close(clientsocket);
    cout << "Socket closed" << endl;
}
