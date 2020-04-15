//
// Created by Ron Dahan on 15/04/2020.
//

#include "votes.h"
#include "mtm_map/map.h"

struct votes_t{
    char **tribes;
    Map *map_area;
    int size;
    int maxSize;
};
