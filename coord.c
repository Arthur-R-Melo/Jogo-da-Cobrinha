#include "coord.h"

int compareCoord(Coord a, Coord b){
    if (a.x == b.x && a.y == b.y)
    {
        return 1;
    }
    
    return 0;
}