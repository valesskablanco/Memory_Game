#include "server.hpp"

using namespace std;

Server::Server()
{

    char *buffer = new char[1024];

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

                    RequestHandler();
                }
            }
        }
    }
}

void Server::requestHandler()
{
    cout << "Handling Request \n" << endl;
    
}
