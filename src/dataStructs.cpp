#include "dataStructs.h"

bool interfere(web a, web b) {
    
    set<int> aLines(a.lines.begin(), a.lines.end());
    set<int> bLines(b.lines.begin(), b.lines.end());
    set<int> aStart(a.start.begin(), a.start.end());
    set<int> aEnd(a.end.begin(), a.end.end());
    set<int> bStart(b.start.begin(), b.start.end());
    set<int> bEnd(b.end.begin(), b.end.end());
    
    for (int line : aLines) {

        if (bLines.count(line)) {

            if ((aStart.count(line) && bEnd.count(line)) ||
                (aEnd.count(line) && bStart.count(line))) {
                continue;
            }

            return true;
        }
    }
    
    return false;
}
