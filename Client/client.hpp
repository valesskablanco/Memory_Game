#ifndef client_h
#define client_h

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#define PORT 10000
#define server_ip "127.0.0.1"

class Client{
    private:
    int clientsocket;
    struct sockaddr_in serverAddress;
    char buffer[1024];
    
    public:
    Client();
    void send();
    void closeSocket();
};
#endif