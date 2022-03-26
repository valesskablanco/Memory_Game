#include "server.hpp"

using namespace std;

Server::Server() {

    char *buffer = new char[1024];
    strcpy(buffer, "Hi, this is Server");

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
        else{

            cout<<"\n Started to listen \n"<<endl;

            //Accept connections
            while (true)
            {
                new_socket = accept(server, (struct sockaddr *)&client_address, &client_len);
                if(new_socket < 0)                   
                {
                    cout<<"\n Error to accept client \n"<<endl;
                }
                else
                {
                    cout<<"\n CLient accepted \n"<<endl;
                }
            

                while (true)
                {
                    int len_request = read(new_socket, buffer_reciever, sizeof(buffer_reciever));
                    if(len_request == -1)
                    {
                        cout<<"Could not read message"<<endl;
                    }
                    else if (len_request == 0){ //not sent 
                        cout<<"Socket closed"<<endl;
                        close(new_socket);
                        break;
                    }
                    else{
                        write(new_socket, buffer,strlen(buffer));
                        cout << "SERVER" << buffer_reciever << endl;
                        handeling_message(buffer_reciever);
                    }
                }
            }


        }
    }
    
}

void Server::handeling_message(char message[1024]){
    //handle client messages (pending)
    std::cout<<"Mensaje: "<<message<<" en handeling message"<<std::endl;
}