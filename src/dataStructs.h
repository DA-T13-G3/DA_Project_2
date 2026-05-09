#ifndef DA_PROJECT_2_DATASTRUCTS_H
#define DA_PROJECT_2_DATASTRUCTS_H

#include <string>
#include "map"
#include "unordered_map"
#include <vector>

using namespace std;

enum alg_type {
    basic,
    splitting,
    spilling
};

struct algorithm { //struct for parser to store information about the second input file
    alg_type type;
    int val;
};

struct web { //struct for storing information about each web
    string var_name;
    vector<int> start;
    vector<int> end;
    vector<int> lines;
};


struct params { //has all information from the input files after being parsed
    vector<web> webs;
    algorithm alg;
    int regs;

    bool valid;
};

struct assignment { //webs that dont interfere with eachother
    vector<web> webs;
};

struct result { //final result of the algorithm
    vector<web> webs;
    vector<assignment> assignments;
    int regs;
    bool possible;
};

struct order { //struct for storing the order of webs
    int index;
    web w;
};

bool interfere(web a, web b);

#endif