#ifndef server_h
#define server_h

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
#include "../Utils/common.hpp"

class Server{
    private: 
    int server, client;
    struct sockaddr_in server_address, client_address;
    int message_len;
    unsigned int client_len;
    int server_len;
    char buffer[1024];


    public:
    Server();
    void RequestHandler();
};
#endif