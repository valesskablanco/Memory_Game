#include "server.hpp"

using namespace std;

/**
 * @brief Construct a new Server object
 * Creates the server interface
 * Creates a socket
 */
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

    thread run_server(&Server::run, this);
    run_server.detach();
}

void Server::run()
{
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
                    while (true)
                    {
                        read(client, this->buffer, BUFFER_SIZE);
                        requestHandler();
                    }
                }
            }
        }
    }
}
/**
 * @brief Manages the requests from the client
 */
void Server::requestHandler()
{
    char operation = this->buffer[0];

    if (operation == '0')
    {
        // return 0 or 1 (if it is in memory) and encoded img
        int i = this->buffer[1] - '0';
        int j = this->buffer[2] - '0';

        card Card = pagedMemory.getFCard(i, j);

        Card.encodeImg();

        memset(this->buffer, 0, sizeof(this->buffer));

        // char verify
        this->buffer[0] = pagedMemory.getCardfromMemory(i, j);

        // image size
        int img_size = Card.img.size();
        this->buffer[1] = img_size / 100;
        this->buffer[2] = (img_size / 10) % 10;
        this->buffer[3] = img_size % 10;

        // Writing buffer

        for (int i = 0; i < img_size; ++i)
        {
            this->buffer[i + 4] = Card.img[i];
        }

        write(client, this->buffer, img_size + 4);
    }
    else if (operation == '1')
    {
        int i1 = this->buffer[1] - '0';
        int j1 = this->buffer[2] - '0';
        int i2 = this->buffer[3] - '0';
        int j2 = this->buffer[4] - '0';

        // return 0 or 1
        char equals = pagedMemory.verify(i1, j1, i2, j2);
        memset(this->buffer, 0, sizeof(this->buffer));
        strcpy(this->buffer, &equals);
        write(client, this->buffer, 1);
    }

}

/**
 * @brief Gets the memory size from the paged memory
 * @return int
 */
int Server::getMemorySize()
{
    return this->pagedMemory.getMemorySize();
}

/**
 * @brief Gets the page faults from paged memory
 * @return int
 */
int Server::getPageFaults()
{
    return this->pagedMemory.getPageFaults();
}

/**
 * @brief Gets the page hits from paged memory
 * @return int
 */
int Server::getPageHits()
{
    return this->pagedMemory.getPageHits();
}