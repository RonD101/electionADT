//
// Created by yoav on 14/04/2020.
//

#include "mtm_map/map.h"
#include "election.h"
#include "votes.h"
#include <string.h>
#include <stdlib.h>

#define LAST_DIGIT 10
#define FIRST_NUMBER '0'
#define FIRST_LOWER_CASE_LETTER 'a'
#define LAST_LOWER_CASE_LETTER 'z'
#define SPACE ' '

static char* toString(int num);
static int toInt(char* str);
bool stringValid(const char*);

struct election_t
{
    Map areas;
    Map tribes;
    Votes votes;
};

void electionDestroy(Election election)
{
    if(election != NULL)
    {
        //Destroys all properties under election via mapADT and votesADT
        mapDestroy(election->areas);
        mapDestroy(election->tribes);
        voteDestroy(election->votes);
    }
}

ElectionResult electionAddTribe(Election election, int tribe_id, const char* tribe_name)
{
    if(election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    if(tribe_id < 0)
    {
        return ELECTION_INVALID_ID;
    }
    char* str = toString(tribe_id);
    if(mapContains(election->tribes, str))
    {
        return ELECTION_TRIBE_ALREADY_EXIST;
    }
    free(str);
    if(!(stringValid(tribe_name)))
    {
        return ELECTION_INVALID_NAME;
    }
    return ELECTION_SUCCESS;
}

//checks if string passed is all lower case letters + spaces and returns true/false
bool stringValid(const char* str)
{
    int len = strlen(str);
    for(int i = 0; i < len; i++)
    {
        if(!(str[i] > FIRST_LOWER_CASE_LETTER && str[i] < LAST_LOWER_CASE_LETTER))
        {
            if(str[i] != SPACE)
            {
                return false;
            }
        }
    }
    return true;
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