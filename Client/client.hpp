#ifndef client_h
#define client_h

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include "../Utils/common.hpp"

class Client
{
private:
    int clientsocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];
    char ch;

public:
    Client();
    void requestHandler();
    void send(char Request[BUFFER_SIZE]);
    void closeSocket();
    void decodeImg(string img);
};
#endif