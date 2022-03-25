#include "client.h"

using namespace std;

Client::Client(){

    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(server_ip);
}

void Client::conection(){

    char *buffer_trasmiter = new char[1024];
    buffer_trasmiter = "Hi, this is Client";
    
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientsocket < 0)
    {
        cout<<"\n Socket creation error \n"<<endl; 
    }
    else{
        cout<<"\n Socket connection successful \n"<<endl;
        
    }

    if (connect(clientsocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cout<<"\n Connection failed \n"<<endl;
    }
    else{
        cout<<"\n Connection to server succesfully \n"<<endl;
    }

    write(clientsocket, buffer_trasmiter, strlen(buffer_trasmiter));
    cout<<"\n Hello message sent \n"<<endl;

    len_response = read(clientsocket, buffer_reciever, sizeof(buffer_reciever));

    if(len_response==-1){
        cout<<"Could not read message"<<std::endl;
    }
    else if (len_response==0){//did not send 
        cout<<"Empty message"<<endl;
    }
    else{
        cout<<buffer_reciever<<endl;
    }

    close(clientsocket);
}