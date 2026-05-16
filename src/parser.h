#ifndef DA_PROJECT_2_PARSER_H
#define DA_PROJECT_2_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <unistd.h>
#include <set>
#include <algorithm>
#include "dataStructs.h"

void parse1(string path1, params1 &params);

void parse2(string path2, params2 &params);

params parse(params1 &params1, params2 &params2);

#endif