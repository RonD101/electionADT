//
// Created by yoav on 14/04/2020.
//

#include "mtm_map/map.h"
#include "election.h"
#include <string.h>
#include <math.h>

static char* toString(int num);
static int toInt(char* str);

struct election_t
{
    Map zones;
    Map *tribes;
};


static char* toString(int num){

}

static int toInt(char* str)
{
    int i = strlen(str);
    int num = 0;
    while(i > 0)
    {
        num += str[i - 1] * pow(10, strlen(str) - i);
        i--;
    }
    return num;
}