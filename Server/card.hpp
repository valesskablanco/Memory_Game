#ifndef card_h
#define card_h

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

class card
{
public:
    int i, j, ID, status;
    std::string img;
    card(int i, int j, int ID, int status);
    void getImage(int ID);
    void print();
};

#endif /* card_h */
