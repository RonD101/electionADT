//
// Created by Ron Dahan on 15/04/2020.
//

#ifndef ELECTIONADT_VOTES_H
#define ELECTIONADT_VOTES_H

#include <stdbool.h>

typedef struct votes_t* Votes;

typedef enum VoteResult_t {
    VOTES_OUT_OF_MEMORY,
    VOTES_NULL_ARGUMENT,
    VOTES_SUCCESS,
    VOTES_INVALID_ID,
    VOTES_TRIBE_ALREADY_EXIST,
    VOTES_AREA_ALREADY_EXIST,
    VOTES_TRIBE_NOT_EXIST,
    VOTES_AREA_NOT_EXIST,
    VOTES_INVALID_VOTES
} VoteResult;

Votes voteCreate();

void voteDestroy(Votes vote);

VoteResult voteAddTribe(Votes vote, int tribe_id);

VoteResult voteAddArea(Votes vote, int area_id, int tribe_id,int votes_num);

VoteResult voteRemoveTribe(Votes vote, int tribe_id);

VoteResult voteRemoveArea(Votes vote, int area_id);

VoteResult voteAdd(Votes vote, const int tribe_id, const int area_id, const int votes_num);

int voteTribeContain(Votes vote,int tribe_id);

int voteNumOfVotes(Votes vote, int area_id, int tribe_id);

static char* toString(int num);

static int toInt(char* str);

static VoteResult expand(Votes map);

char* voteMostVoted(Votes vote, char* area_id_str);

#endif //ELECTIONADT_VOTES_H
