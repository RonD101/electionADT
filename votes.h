//
// Created by Ron Dahan on 15/04/2020.
//

#ifndef ELECTIONADT_VOTES_H
#define ELECTIONADT_VOTES_H

#include <stdbool.h>

/**
* Vote Container
*
* Implements a vote container type.
* The type of the key and the value is string (char *)
*
* The following functions are available:
*   voteCreate		- Creates a new empty vote
*   voteDestroy		- Deletes an existing vote and frees all resources
*   voteAddTribe	- Adds tribe
*   voteAddArea  	- Adds map object (area)
*   voteRemoveTribe	- Removes a tribe that matches the given element of tribe_id
*   voteRemoveArea	- Removes a map container that matches the given element of area_id
*   voteAdd		    - Advances the internal iterator to the next key and                            ++++++++++
*	voteTribeContain - Returns whether or not a tribe that matches the given element of tribe_id exists
*   voteNumOfVotes	- Creates a new empty map                           ++++++++++
*   voteMostVoted	- Creates a new empty map                           ++++++++++
*/

/** Type for defining the votes */
typedef struct votes_t* Votes;

/** Type used for returning error codes from votes functions */
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

/**
* voteCreate: Allocates a new empty vote.
*
* @return
* 	NULL - if allocations failed.
* 	A new vote in case of success.
*/
Votes voteCreate();

/**
* voteDestroy: Deallocates an existing vote. Clears all elements.
*
* @param vote - Target vote to be deallocated. If vote is NULL nothing will be
* 		done
*/
void voteDestroy(Votes vote);

/**
*	voteAddTribe: Adds a new tribe.
*
* @param vote - The vote for which to add the tribe element
* @param tribe_idElement - The tribe_id element which needs to be added.
*       An area map is also added
* @return
* 	VOTES_NULL_ARGUMENT if one of the params is NULL
 * 	VOTES_INVALID_ID if tribe_id is negative
 * 	VOTES_TRIBE_ALREADY_EXIST if vote already contains a tribe with the tribe_id element
* 	VOTES_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	VOTES_SUCCESS the elements had been inserted successfully
*/
VoteResult voteAddTribe(Votes vote, int tribe_id);

/**
*	voteAddArea: Adds a new area.
*
* @param vote - The vote for which to add the area element
* @param area_idElement - The area_id element which needs to be added.
* @param tribe_idElement - The tribe_id element to which the area_idElement needs to be added.
* @param votes_num - Number of votes from area_id to tribe_id to be added
* @return
* 	VOTES_NULL_ARGUMENT if one of the params is NULL
* 	VOTES_INVALID_ID if area_id or tribe_id is negative
* 	VOTES_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	VOTES_SUCCESS the elements had been inserted successfully
*/
VoteResult voteAddArea(Votes vote, int area_id, int tribe_id,int votes_num);

/**
*  voteRemoveTribe: Removes a pair of tribe element and area map from the vote. The elements
*  are found using the comparison function voteTribeContain. Once found,
*  the elements are removed and deallocated.
*
* @param vote -
* 	The vote to remove the elements from.
* @param tribe_idElement
* 	The tribe_id element to find and remove from the vote.
* 	The area map associated with this tribe will be destroyed.
* @return
*  VOTES_NULL_ARGUMENT if one of the params is NULL
*  VOTES_TRIBE_NOT_EXIST if tribe matching the tribe_id doesn't already exist in the vote
*  VOTES_SUCCESS the paired elements had been removed successfully
*/
VoteResult voteRemoveTribe(Votes vote, int tribe_id);

/**
*  voteRemoveArea: Removes a area maps from the vote. Once found,
*  the maps are removed and deallocated.
*
* @param vote -
* 	The vote to remove the elements from.
* @param area_idElement
*   The area_id to find and remove from the vote.
* @return
*  VOTES_NULL_ARGUMENT if one of the params is NULL
*  VOTES_SUCCESS the elements had been removed successfully or no such area exists
*/
VoteResult voteRemoveArea(Votes vote, int area_id);

/**
*  voteAdd: Adds a number of votes from one area to one tribe.
*
* @param vote -
* 	The vote for which to update the number of votes.
* @param tribe_idElement
*   The tribe_id to find and remove from the vote.
* @param area_idElement
* @return
*  VOTES_NULL_ARGUMENT if one of the params is NULL
*  VOTES_SUCCESS the elements had been removed successfully or no such area exists
*/
VoteResult voteAdd(Votes vote, const int tribe_id, const int area_id, int votes_num);

int voteTribeContain(Votes vote,int tribe_id);

int voteNumOfVotes(Votes vote, int area_id, int tribe_id);


char* voteMostVoted(Votes vote, char* area_id_str);

#endif //ELECTIONADT_VOTES_H
