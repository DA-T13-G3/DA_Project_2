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

void mergeWebs(params &params) {
    map<string, vector<int>> websMap;
    
    for (int i = 0; i < params.webs.size(); i++) {
        websMap[params.webs[i].var_name].push_back(i);
    }
    
    vector<web> finalWebs;
    set<int> processed;
    
    for (auto& [name, indices] : websMap) {
        vector<bool> merged(indices.size(), false);
        
        for (int i = 0; i < indices.size(); i++) {
            if (merged[i]) continue;
            
            set<int> mergedLines(params.webs[indices[i]].lines.begin(), params.webs[indices[i]].lines.end());
            set<int> mergedStart(params.webs[indices[i]].start.begin(), params.webs[indices[i]].start.end());
            set<int> mergedEnd(params.webs[indices[i]].end.begin(), params.webs[indices[i]].end.end());
            set<int> rmv;
            
            merged[i] = true;
            bool intersects = true;
            
            while (intersects) {
                intersects = false;
                
                for (int j = i + 1; j < indices.size(); j++) {
                    if (merged[j]) continue;
                    
                    set<int> otherLines(params.webs[indices[j]].lines.begin(), params.webs[indices[j]].lines.end());
                    
                    vector<int> intersection;
                    set_intersection(mergedLines.begin(), mergedLines.end(), otherLines.begin(), otherLines.end(), back_inserter(intersection));
                    
                    if (!intersection.empty()) {
                        set<int> otherStart(params.webs[indices[j]].start.begin(), params.webs[indices[j]].start.end());
                        set<int> otherEnd(params.webs[indices[j]].end.begin(), params.webs[indices[j]].end.end());
                        
                        for (int line : intersection) {
                            rmv.insert(line);
                        }
                        
                        for (int line : otherLines) {
                            mergedLines.insert(line);
                        }
                        for (int line : otherStart) {
                            mergedStart.insert(line);
                        }
                        for (int line : otherEnd) {
                            mergedEnd.insert(line);
                        }
                        
                        merged[j] = true;
                        intersects = true;
                        break;
                    }
                }
            }
            
            for (int line : rmv) {
                mergedStart.erase(line);
                mergedEnd.erase(line);
            }
            
            params.webs[indices[i]].lines.assign(mergedLines.begin(), mergedLines.end());
            params.webs[indices[i]].start.assign(mergedStart.begin(), mergedStart.end());
            params.webs[indices[i]].end.assign(mergedEnd.begin(), mergedEnd.end());
            
            finalWebs.push_back(params.webs[indices[i]]);
            processed.insert(indices[i]);
            
            for (int j = i + 1; j < indices.size(); j++) {

                if (merged[j]) {
                    processed.insert(indices[j]);
                }
            }
        }
    }
    
    for (int i = 0; i < params.webs.size(); i++) {

        if (processed.find(i) == processed.end()) {
            finalWebs.push_back(params.webs[i]);
        }

    }
    
    params.webs = finalWebs;
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
        line = trim(line);
        if(line.empty() || line[0] == '#') {continue;}
        web w;
        string name, data;
        stringstream ss(line);

        getline(ss, name, ':');
        getline(ss, data);

        name = trim(name);
        w.var_name = name;

        stringstream dataStream(data);
        string value;
        while (getline(dataStream, value, ',')){
            value = trim(value);
            if (value.size() > 1){
                if (value.back() == '+'){
                    value.pop_back();
                    w.start.push_back(myStoi(value, params));
                } else if (value.back() == '-'){
                    value.pop_back();
                    w.end.push_back(myStoi(value, params));
                }
            }
            w.lines.push_back(stoi(value));
        }
        webs.push_back(w);

    }
    params.webs = webs;
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
            } else if (line == "free") {
                alg.type = free_;
                alg.val = 0;
                hasAlg = true; //check
                hasVal = true; //check
            } else {
                stringstream valStream(line);
                getline(valStream, line, ',');
                line = trim(line);
                if (line == "splitting"){
                    alg.type = splitting_;
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

void addID(params &params) {
    for (int i = 0; i < params.webs.size(); i++) {
        params.webs[i].id =to_string(i);
    }
}

params parse (string path1, string path2){
    params params;
    params.valid = true;
    parse1(path1, params);
    parse2(path2, params);
    mergeWebs(params);
    addID(params);
    return params;
}

