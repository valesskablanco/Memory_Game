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

using namespace std;

class dataStruct {

    public:
        dataStruct();
        void createFile();
        card getFCard(int i, int j);
        void setFCard(int i, int j, int ID, int status);
        void createPagedMemory(int size);
        int isCardinMemory(int i, int j);
        card getCardfromMemory(int i, int j);
        void printMemory();
        card replaceCard(int i, int j);
        void shuffle();

    private: 
        vector<card> memory;
        int memory_size;
        int matrix_size = 30;
        int flag;
};

#endif