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
static bool stringValid(const char*);

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
    if(!(stringValid(tribe_name)))
    {
        return ELECTION_INVALID_NAME;
    }
    char* str = toString(tribe_id); //makes a copy of tribe_id into a string to pass to function mapContains
    if(str == NULL)
    {
        free(str);
        return ELECTION_OUT_OF_MEMORY;
    }
    if(mapContains(election->tribes, str))
    {
        return ELECTION_TRIBE_ALREADY_EXIST;
    }
    mapPut(election->tribes, str, tribe_name); //adds tribe
    free(str);
    return ELECTION_SUCCESS;
}

ElectionResult electionAddArea(Election election, int area_id, const char* area_name)
{
    if(election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    if(area_id < 0)
    {
        return ELECTION_INVALID_ID;
    }
    if(!(stringValid(area_name)))
    {
        return ELECTION_INVALID_NAME;
    }
    char* str = toString(area_id); //makes a copy of area_id into a string to pass to function mapContains
    if(str == NULL)
    {
        free(str);
        return ELECTION_OUT_OF_MEMORY;
    }
    if(mapContains(election->tribes, str))
    {
        return ELECTION_AREA_ALREADY_EXIST;
    }
    mapPut(election->areas, str, area_name); //adds area
    free(str);
    return ELECTION_SUCCESS;
}

ElectionResult electionAddVote (Election election, int area_id, int tribe_id, int num_of_votes)
{
    if(election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    if(area_id < 0 || tribe_id < 0)
    {
        return ELECTION_INVALID_ID;
    }
    if(num_of_votes <= 0)
    {
        return ELECTION_INVALID_VOTES;
    }
    char* str = toString(area_id); //makes a copy of area_id into a string to pass to function mapContains
    if(str == NULL)
    {
        free(str);
        return ELECTION_OUT_OF_MEMORY;
    }
    if(!(mapContains(election->areas, str)))
    {
        return ELECTION_AREA_NOT_EXIST;
    }
    free(str);
    str = toString(tribe_id); //makes a copy of tribe_id into a string to pass to function mapContains
    if(str == NULL)
    {
        free(str);
        return ELECTION_OUT_OF_MEMORY;
    }
    if(!(mapContains(election->tribes, str)))
    {
        return ELECTION_TRIBE_NOT_EXIST;
    }
    free(str);
    voteAdd(election->votes, tribe_id, area_id, num_of_votes); //uses function from votesADT to add votes
    return ELECTION_SUCCESS;
}
ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    if(election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    if(area_id < 0 || tribe_id < 0)
    {
        return ELECTION_INVALID_ID;
    }
    if(num_of_votes <= 0)
    {
        return ELECTION_INVALID_VOTES;
    }
    char* str = toString(area_id); //makes a copy of area_id into a string to pass to function mapContains
    if(str == NULL)
    {
        free(str);
        return ELECTION_OUT_OF_MEMORY;
    }
    if(!(mapContains(election->areas, str)))
    {
        return ELECTION_AREA_NOT_EXIST;
    }
    free(str);
    str = toString(tribe_id); //makes a copy of tribe_id into a string to pass to function mapContains
    if(str == NULL)
    {
        free(str);
        return ELECTION_OUT_OF_MEMORY;
    }
    if(!(mapContains(election->tribes, str)))
    {
        return ELECTION_TRIBE_NOT_EXIST;
    }
    free(str);
    voteAdd(election->votes, tribe_id, area_id, -num_of_votes); //uses function from votesADT to remove votes

    //checks via function from votesADT if num of votes of a tribe is now negative,
    //if so uses function voteAdd to change num of votes to 0
    int votes_num = voteNumOfVotes(election->votes, area_id, tribe_id);
    if(votes_num < 0)
    {
        voteAdd(election->votes, tribe_id, area_id, -votes_num);
    }
    return ELECTION_SUCCESS;
}


//checks if string passed is all lower case letters + spaces and returns true/false
static bool stringValid(const char* str)
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