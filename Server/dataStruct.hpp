#ifndef dataStruct_h
#define dataStruct_h


#define MATRIX_SIZE 30
#include "../Utils/common.hpp"
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

using namespace std;

class dataStruct {

    public:
        dataStruct();
        void createFile();
        card getFCard(int i, int j);
        void setFCard(int i, int j, int ID, int status);
        void createPagedMemory(int size);
        int isCardinMemory(int i, int j);
        char getCardfromMemory(int i, int j);
        void printMemory();
        void replaceCard(int i, int j);
        void shuffle();
        char verify(int i1, int j1, int i2, int j2);

    private: 
        vector<card> memory;
        int memory_size;
        int matrix_size = 30;
        int flag;
};

#endif