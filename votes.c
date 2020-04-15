//
// Created by Ron Dahan on 15/04/2020.
//

#include "votes.h"
#include "mtm_map/map.h"
#include <stdlib.h>

#define INITIAL_SIZE 2
#define EXPAND_FACTOR 2
#define LAST_DIGIT 10
#define FIRST_NUMBER '0'

struct votes_t{
    char **tribes;
    Map *map_area;
    int size;
    int maxSize;
};

Votes voteCreate(){
    Votes vote = malloc(sizeof(*vote));
    if(vote == NULL){
        return NULL;
    }
    vote->tribes = malloc(sizeof(char*)*INITIAL_SIZE);
    vote->map_area = malloc(sizeof(Map)*INITIAL_SIZE);
    if(vote->tribes == NULL || vote->map_area == NULL){
        free(vote->tribes);
        free(vote->map_area);
        free(vote);
        return  NULL;
    }
    vote->size = 0;
    vote->maxSize = INITIAL_SIZE;
    return vote;
}

VoteResult voteAddArea(Votes vote, int area_id, int tribe_id,int votes_num){
    if(vote == NULL ){
        return VOTES_NULL_ARGUMENT;
    }
    if(area_id < 0 || tribe_id < 0){
        return VOTES_INVALID_ID;
    }
    int tribe_num = voteTribeContain(vote,tribe_id);
    if(tribe_num == -1){
        if(voteAddTribe(vote,tribe_id) == VOTES_OUT_OF_MEMORY){
            return VOTES_OUT_OF_MEMORY;
        }
    }
    if(mapPut(vote->map_area[tribe_num],toString(area_id),toString(votes_num)) == MAP_OUT_OF_MEMORY){
        return VOTES_OUT_OF_MEMORY;
    }
    return VOTES_SUCCESS;
}

static char* toString(int num){
    int temp = num,counter = 0;
    while (temp){
        counter++;
        temp /= LAST_DIGIT;
    }
    char *str = malloc(sizeof(char)*counter + 1);
    if(str == NULL){
        return NULL;
    }
    for (int i = counter-1; i >= 0; --i) {
        str[i] = num%LAST_DIGIT + FIRST_NUMBER;
        num /= 10;
    }
    str[counter] = 0;
    return str;
}

static int toInt(char* str)
{
    int len = strlen(str);
    int num = 0;
    for (int j = 0; j < len; ++j) {
        num *= LAST_DIGIT;
        num += str[j] - FIRST_NUMBER;
    }
    return num;
}

int voteTribeContain(Votes vote, int tribe_id){
    for (int i = 0; i < vote->size; ++i) {
        if(toInt(vote->tribes[i]) == tribe_id){
            return i;
        }
    }
    return -1;
}
