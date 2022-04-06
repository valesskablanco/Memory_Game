#ifndef dataStruct_h
#define dataStruct_h


#define CARD_TYPES
#include "card.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime> 

class dataStruct {

    public:
        void createFile();
        card getCard(int i, int j);
        void setCard(int i, int j, int ID, int status);
};

#endif