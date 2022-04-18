#include "server.hpp"

using namespace std;

Server::Server()
{
    // creating the paged memory

    server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0)
    {
        cout << "\n Server Error \n"
             << endl;
    }
    else
    {
        cout << "\n Server Initialized \n"
             << endl;
    }

    // Cleaning struct
    memset(&server_address, 0, sizeof(server_len));

    // Initialize struct
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(PORT);

    // Bind the socket to the local port
    if (bind(server, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        cout << "\n Bind error" << endl;
    }
    else
    {
        cout << "Bind succesfull" << endl;

        // Listen request from client
        if (listen(server, 3) < 0)
        {
            cout << "\n Error listening \n"
                 << endl;
        }
        else
        {

            cout << "\n Started to listen \n"
                 << endl;

            // Accept connections
            while (true)
            {
                client = accept(server, (struct sockaddr *)&client_address, &client_len);
                if (client < 0)
                {
                    cout << "\n Error to accept client \n"
                         << endl;
                }
                else
                {
                    cout << "\n Client accepted \n"
                         << endl;

                    read(client, this->buffer, BUFFER_SIZE);
                    requestHandler();
                }
            }
        }
    }
}

void Server::requestHandler()
{
    cout << "Handling Request \n"
         << endl;

    char operation = this->buffer[0];

    if (operation == '0')
    {
        // return encoded img
        int i = this->buffer[1];
        int j = this->buffer[2];

        card Card = pagedMemory.getFCard(i, j);
        int ID = Card.ID;

        Card.encodeImg(Card.getPath(ID)); //PROBLEMA CON ESTO
        strcpy(this->buffer, Card.img);
    }
    else if (operation == '1')
    {
        int i1 = this->buffer[1];
        int j1 = this->buffer[2];
        int i2 = this->buffer[3];
        int j3 = this->buffer[4];

        // return 0 or 1
        strcpy(this->buffer, "verifying equals\0");
    }

    write(client, this->buffer, strlen(this->buffer));
}
