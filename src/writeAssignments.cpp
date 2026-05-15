#include "writeAssignments.h"
#include <fstream>
#include <set>

using namespace std;

void write(const result &res) {
    ofstream output("../output/output.txt");
    
    if (!output.good()) return;

    output << "# Total number of webs followed by the listing of the program points of each one" << endl;
    output << "# program points in each web are sorted in ascending order" << endl;
    
    int totalWebs = (int)res.webs.size() + (int)res.spilledWebs.size();
    output << "webs: " << totalWebs << endl;

    auto writeWebLine = [&](const web& w, int index) {
        output << "web" << w.id << ": ";
        set<int> allLines(w.lines.begin(), w.lines.end());
        set<int> startSet(w.start.begin(), w.start.end());
        set<int> endSet(w.end.begin(), w.end.end());
        
        bool first = true;
        for (int line : allLines) {
            if (!first) output << ",";
            output << line;
            if (startSet.count(line)) output << "+";
            if (endSet.count(line)) output << "-";
            first = false;
        }
        output << endl;
    };

    for (int i = 0; i < (int)res.webs.size(); i++) {
        writeWebLine(res.webs[i], i);
    }

    for (int i = 0; i < (int)res.spilledWebs.size(); i++) {
        writeWebLine(res.spilledWebs[i], i + (int)res.webs.size());
    }
    
    output << "# Total number of registers used, followed by assignment to webs" << endl;
    if (res.possible){
        output << "registers: " << res.regs << endl;
    } else {
        output << "registers: 0" << endl;
    }
    
    //printf("%d",res.possible);

    if (!res.possible) {

        for (int i = 0; i < (int)res.webs.size(); i++) {
            output << "M: web" << i << endl;
        }

    } else {

        for (int i = 0; i < (int)res.assignments.size(); i++) {

            for (const auto& aWeb : res.assignments[i].webs) {

                output << "r" << i << ": web";

                for (int k = 0; k < (int)res.webs.size(); k++) {
                    if (res.webs[k].var_name == aWeb.var_name && res.webs[k].lines == aWeb.lines) {
                        output << res.webs[k].id;
                        break;
                    }
                }
                output << endl;
            }
        }
    }

    for (int i = 0; i < (int)res.spilledWebs.size(); i++){
        output << "M(spilled): web" << i + (int)res.webs.size() << endl;
    }
    
    output.close();
}