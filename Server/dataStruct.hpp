#ifndef dataStruct_h
#define dataStruct_h


#define MATRIX_SIZE 30
#define ROWS 5
#define COLUMNS 6
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
        card getFCard(int i, int j);
        void setFCard(int i, int j, int ID, int status);
};

#endif