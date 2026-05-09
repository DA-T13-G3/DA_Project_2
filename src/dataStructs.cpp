#include "dataStructs.h"

bool interfere(web a, web b) {
    return (a.start < b.end && b.start < a.end);
}
