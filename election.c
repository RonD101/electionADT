//
// Created by yoav on 14/04/2020.
//

#include "mtm_map/map.h"
#include "election.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

//char* toString(int num);
//int toInt(char* str);

struct election_t
{
    Map zones;
    Map *tribes;
};


char* toString(int num){
    int temp = num,counter = 0;
    while (temp){
        counter++;
        temp /= 10;
    }
    char *str = malloc(sizeof(char)*counter + 1);
    if(str == NULL){
        return NULL;
    }
    for (int i = counter-1; i >= 0; ++i) {
        str[i] = num%10 + '0';
        num /= 10;
    }
    str[counter] = 0;
    return str;
}

int toInt(char* str)
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