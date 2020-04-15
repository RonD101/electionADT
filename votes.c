//
// Created by Ron Dahan on 15/04/2020.
//

#include "votes.h"
#include "mtm_map/map.h"
#include <stdlib.h>
#include <assert.h>

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

void voteDestroy(Votes vote)
{
    if(vote != NULL)
    {
        for(int i = 0; i < vote->size; i++)
        {
            mapDestroy(vote->map_area[i]); //uses mapADT function to destroy each area
        }
        free(vote->tribes); //deallocates memory from tribes
        free(vote); //deallocates memory from the vote struct
    }
}

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

VoteResult voteAddTribe(Votes vote, int tribe_id)
{
    if(vote == NULL)
    {
        return VOTES_NULL_ARGUMENT;
    }
    if(toInt(tribe_id) < 0)
    {
        return VOTES_INVALID_ID;
    }
    if(voteTribeContain(vote, tribe_id) >= 0)
    {
        return VOTES_TRIBE_ALREADY_EXIST;
    }
    assert(vote->size < vote->maxSize);
    vote->tribes[vote->size] = toString(tribe_id);
    vote->size++;
    //vote->tribes[vote->size++] = malloc(strlen(toString(tribe_id)));
    //vote->tribes[vote->size] = toString(tribe_id);
    return VOTES_SUCCESS;
}

VoteResult voteRemoveTribe(Votes vote, int tribe_id)
{
    if(vote == NULL)
    {
        return VOTES_NULL_ARGUMENT;
    }
    int index = voteTribeContain(vote, tribe_id);
    if(voteTribeContain(vote, tribe_id) < FIRST_NUMBER)
    {
        return VOTES_TRIBE_NOT_EXIST;
    }
    mapDestroy(vote->map_area[index]);
    free(vote->tribes[index]);
    vote->tribes[index] = vote->tribes[vote->size];
    vote->size--;
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
