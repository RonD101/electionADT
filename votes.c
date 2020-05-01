//
// Created by Ron Dahan on 15/04/2020.
//

#include "votes.h"
#include "mtm_map/map.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INITIAL_SIZE 2
#define EXPAND_FACTOR 2
#define LAST_DIGIT 10
#define FIRST_NUMBER '0'

static char* toString(int num);
static int toInt(char* str);

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
            free(vote->tribes[i]); //deallocates memory from tribes
        }
        free(vote->tribes);
        free(vote->map_area);
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
        tribe_num = voteTribeContain(vote,tribe_id);
    }
    char* area_str = toString(area_id);
    char* vote_num_str = toString(votes_num);
    if(area_str == NULL || vote_num_str == NULL){
        free(area_str);
        free(vote_num_str);
        return VOTES_OUT_OF_MEMORY;
    }
    if(mapPut(vote->map_area[tribe_num],area_str,vote_num_str) == MAP_OUT_OF_MEMORY){
        free(area_str);
        free(vote_num_str);
        return VOTES_OUT_OF_MEMORY;
    }
    free(area_str);
    free(vote_num_str);
    return VOTES_SUCCESS;
}

VoteResult voteAddTribe(Votes vote, int tribe_id)
{
    if(vote == NULL)
    {
        return VOTES_NULL_ARGUMENT;
    }
    if(tribe_id < 0)
    {
        return VOTES_INVALID_ID;
    }
    if(voteTribeContain(vote, tribe_id) >= 0)
    {
        return VOTES_TRIBE_ALREADY_EXIST;
    }
    if(vote->size >= vote->maxSize){
        if(voteExpand(vote) == VOTES_OUT_OF_MEMORY){
            return VOTES_OUT_OF_MEMORY;
        }
    }
    vote->tribes[vote->size] = toString(tribe_id);
    vote->map_area[vote->size] = mapCreate();
    if(vote->map_area[vote->size] == NULL || vote->tribes[vote->size] == NULL){
        mapDestroy(vote->map_area[vote->size]);
        free(vote->tribes[vote->size]);
        return VOTES_OUT_OF_MEMORY;
    }
    vote->size++;
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

VoteResult voteRemoveArea(Votes vote, int area_id)
{
    if(vote == NULL)
    {
        return VOTES_NULL_ARGUMENT;
    }
    for(int i = 0; i < vote->size; i++)
    {
        char* key = toString(area_id);
        if(key == NULL)
        {
            return VOTES_OUT_OF_MEMORY;
        }
        mapRemove(vote->map_area[i], key);
        free(key);
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
    if(str == NULL){
        return -1;
    }
    int len = (int)strlen(str);
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

VoteResult voteAdd(Votes vote, const int tribe_id, const int area_id, int votes_num){
    if(vote == NULL){
        return VOTES_NULL_ARGUMENT;
    }
    if(tribe_id < 0 || area_id < 0){
        return VOTES_INVALID_ID;
    }
    int tribe_num = voteTribeContain(vote, tribe_id);
    if(tribe_num != -1){
        char* key = toString(area_id);
        if(key == NULL){
            return VOTES_OUT_OF_MEMORY;
        }
        if(mapGet(vote->map_area[tribe_num], key) != NULL){//updating the amount of votes
            int new_vote_value = toInt(mapGet(vote->map_area[tribe_num], key)) + votes_num;
            if(new_vote_value < 0){
                new_vote_value = 0;
            }
            char* new_vote_value_str = toString(new_vote_value);
            if(new_vote_value_str == NULL){
                free(key);
                return VOTES_OUT_OF_MEMORY;
            }
            mapPut(vote->map_area[tribe_num],key,new_vote_value_str);
            free(new_vote_value_str);
            free(key);
            return VOTES_SUCCESS;
        }else{//creating a new area for this tribe
            free(key);
            if(votes_num < 0){
                return VOTES_INVALID_VOTES;
            }
            if(voteAddArea(vote,area_id,tribe_id,votes_num) == VOTES_OUT_OF_MEMORY){
                return VOTES_OUT_OF_MEMORY;
            }
            return VOTES_SUCCESS;
        }
    } else{//creating a new tribe and area with associated number of votes
        if(votes_num < 0){
            votes_num = 0;
        }
        if(vote->size == vote->maxSize){
            if(voteExpand(vote) == VOTES_OUT_OF_MEMORY){
                return VOTES_OUT_OF_MEMORY;
            }
        }
        if(voteAddTribe(vote,tribe_id) == VOTES_OUT_OF_MEMORY){
            return VOTES_OUT_OF_MEMORY;
        }
        if(voteAddArea(vote,area_id,tribe_id,votes_num) == VOTES_OUT_OF_MEMORY){
            voteRemoveTribe(vote,tribe_id);
            return VOTES_OUT_OF_MEMORY;
        }
        return VOTES_SUCCESS;
    }
}

VoteResult voteExpand(Votes vote){
    int newSize = EXPAND_FACTOR * vote->maxSize;
    char **new_tribes = realloc(vote->tribes,sizeof(char*)*newSize);
    Map *new_map_area = realloc(vote->map_area, sizeof(Map)*newSize);
    if (new_tribes == NULL || new_map_area == NULL) {
        free(new_map_area);
        free(new_tribes);
        return VOTES_OUT_OF_MEMORY;
    }
    //updating the pointers
    vote->tribes = new_tribes;
    vote->map_area = new_map_area;
    vote->maxSize = newSize;
    return VOTES_SUCCESS;
}

char* voteMostVoted(Votes vote, char* area_id_str){
    if(vote == NULL || area_id_str == NULL){
        return NULL;
    }
    int most_num_of_votes = 0;
    char* mostVotedTribe = NULL;
    int votes_num;
    for (int i = 0; i < vote->size; ++i) {
        votes_num = toInt(mapGet(vote->map_area[i],area_id_str)); // checking how many voted to this tribe in this area
        if(votes_num == -1){// vote_num is equal to -1 when no one voted for this tribe so we updating it to 0
            votes_num = 0;
        }
        if(votes_num > most_num_of_votes){ //updating the most voted number and it's name
            most_num_of_votes = votes_num;
            mostVotedTribe = vote->tribes[i];
        } else if(votes_num == most_num_of_votes){ //dealing with the case of the same number of vote and choosing the lower id.
            if(toInt(vote->tribes[i]) < toInt(mostVotedTribe) || toInt(mostVotedTribe) == -1){
                most_num_of_votes = votes_num;
                mostVotedTribe = vote->tribes[i];
            }
        }
    }
    return mostVotedTribe;
}



int voteNumOfVotes(Votes vote, int area_id, int tribe_id)
{
    if(vote == NULL )
    {
        return VOTES_NULL_ARGUMENT;
    }
    if(area_id < 0 || tribe_id < 0)
    {
        return VOTES_INVALID_ID;
    }
    int tribe_num = voteTribeContain(vote,tribe_id);
    if(tribe_num == -1)
    {
        if(voteAddTribe(vote,tribe_id) == VOTES_OUT_OF_MEMORY)
        {
            return VOTES_OUT_OF_MEMORY;
        }
    }
    char* str = toString(area_id);
    if(str == NULL)
    {
        free(str);
        return VOTES_OUT_OF_MEMORY;
    }
    int votes_num = toInt(mapGet(vote->map_area[tribe_num], str));
    free(str);
    return votes_num;
}
