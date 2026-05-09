#include "writeAssignments.h"

using namespace std;

void write(const result &res, string outputPath) {
    ofstream outfile(outputPath);
    
    if (!outfile.good()) {
        return;
    }

    outfile << "# Total number of webs followed by the listing of the program points of each one" << endl;
    outfile << "# program points in each web are sorted in ascending order" << endl;
    
    outfile << "webs: " << res.webs.size() << endl;
    for (int i = 0; i < res.webs.size(); i++) {
        
        outfile << "web" << i << ": ";
        
        set<int> allLines(res.webs[i].lines.begin(), res.webs[i].lines.end());
        set<int> startSet(res.webs[i].start.begin(), res.webs[i].start.end());
        set<int> endSet(res.webs[i].end.begin(), res.webs[i].end.end());
        
        bool first = true;
        for (int line : allLines) {
            if (!first) outfile << ",";
            outfile << line;
            if (startSet.count(line)) outfile << "+";
            if (endSet.count(line)) outfile << "-";
            first = false;
        }
        outfile << endl;
    }
    
    outfile << "# Total number of registers used, followed by assignment to webs" << endl;

    outfile << "registers: " << res.regs << endl;
    
    if (!res.possible) {
        for (int i = 0; i < res.webs.size(); i++) {
            outfile << "M: web" << i << endl;
        }
    } else {
        for (int i = 0; i < res.assignments.size(); i++) {
            for (int j = 0; j < res.assignments[i].webs.size(); j++) {
                outfile << "r" << i << ": web";
                for (int k = 0; k < res.webs.size(); k++) {
                    if (res.webs[k].var_name == res.assignments[i].webs[j].var_name &&
                        res.webs[k].lines == res.assignments[i].webs[j].lines) {
                        outfile << k;
                        break;
                    }
                }
                outfile << endl;
            }
        }
    }
    
    outfile.close();


}