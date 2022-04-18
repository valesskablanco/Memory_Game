#ifndef card_h
#define card_h

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
class card
{
public:
    int i, j, ID, status;
    string path;
    string img;
    card(int i, int j, int ID, int status);
    void getPath(int ID);
    void print();
    void encodeImg(string path);

private:
    char ch;
};

#endif /* card_h */
