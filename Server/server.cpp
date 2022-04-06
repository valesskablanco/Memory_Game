#include "server.hpp"


using namespace std;

Server::Server() {

    char *buffer = new char[1024];

    server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0){
        cout << "\n Server Error \n"
             << endl;
    } 
    else{
        cout << "\n Server Initialized \n"
             << endl;
    }

    //Cleaning struct 
    memset(&server_address, 0, sizeof(server_len));
    
    //Initialize struct
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(PORT);

    //Bind the socket to the local port
    if (bind(server, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        cout << "\n Bind error" << endl;
    }
    else
    {
        cout << "Bind succesfull" << endl;

        //Listen request from client
        if (listen(server, 3) < 0)
        {
            cout<<"\n Error listening \n"<<endl;
        }
        else
        {

            cout<<"\n Started to listen \n"<<endl;

            //Accept connections
            while (true)
            {
                client = accept(server, (struct sockaddr *)&client_address, &client_len);
                if(client < 0)                   
                {
                    cout<<"\n Error to accept client \n"<<endl;
                }
                else
                {
                    cout<<"\n Client accepted \n"<<endl;

                    int message_len = read(client, buffer, sizeof(buffer));
                    if(message_len == -1){

                        cout << "Could not read message" << endl;

                    }else if (message_len == 0){

                        //did not send
                        cout << "Socket closed" << endl;
                        close(client);
                        break;

                    }else{
                        
                        write(client,buffer,strlen(buffer));
                        RequestHandler(buffer);
                    }
                    
                }
            }

        }
    }
    
}

void Server::RequestHandler(char Request[1024]){
    cout << "Handling Request for: " << Request << endl;
}

void Server::CloseSocket()
    {
        close(client);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }