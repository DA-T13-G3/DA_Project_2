#include "parser.h"

using namespace std;

string trim(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, (last - first + 1));
}

int myStoi(string s, params &params){
    int i;
    try {
        i = stoi(s);
        return i;
    } catch (...) {
        params.valid = false;
        return -1;
    }
}

vector<range> merge(vector<range>){
    
}

void parse1(string path1, params &params) {
    vector<web> webs;

    ifstream filestream(path1);
    string line;

    if (!filestream.good()){
        params.valid = false;
        return;
    }

    while (getline(filestream, line)){

    }
}

void parse2(string path, params &params){
    bool hasRegs = false;
    bool hasAlg = false;
    bool hasVal = false;
    int regs = 0;
    algorithm alg;
    ifstream filestream(path);
    string line;

    if (!filestream.good()){
        params.valid = false;
        return;
    }

    while (getline(filestream, line)){
        line = trim(line);
        if(line.empty() || line[0] == '#') {continue;}
        stringstream lineStream(line);
        getline(lineStream, line, ':');
        if (line == "registers"){
            getline(lineStream, line);
            line = trim(line);
            regs = myStoi(line, params);
            hasRegs = true; //check
        } else if (line == "algorithm"){
            getline(lineStream, line);
            line = trim(line);
            if (line == "basic"){
                alg.type = basic;
                alg.val = 0;
                hasAlg = true; //check
                hasVal = true; //check
            } else {
                stringstream valStream(line);
                getline(valStream, line, ',');
                line = trim(line);
                if (line == "splitting"){
                    alg.type = splitting;
                    hasAlg = true; //check
                } else if (line == "spilling"){
                    alg.type = spilling;
                    hasAlg = true; //check
                }
                getline(valStream, line);
                line = trim(line);
                alg.val = myStoi(line, params);
                hasVal = true; //check
            }
        }
    }

    if (!(hasRegs && hasAlg && hasVal)) { //check
        params.valid = false;
    }

    params.alg = alg;
    params.regs = regs;
}

params parse (string path1, string path2){
    params params;
    params.valid = true;
    parse1(path1, params);
    parse2(path2, params);
    return params;
}

int main(){
    params params = parse("test1.txt", "test2.txt");
    cout << "is Valid: " << params.valid << endl;
    cout << "Regs: " << params.regs << endl;
    cout << "Alg type: " << params.alg.type << endl;
    cout << "Alg val: " << params.alg.val << endl;
    for (web w : params.webs){
        cout << "Name: " << w.var_name << endl;
        cout << "Start: " << w.start << endl;
        cout << "End: " << w.end << endl;
    }
}
