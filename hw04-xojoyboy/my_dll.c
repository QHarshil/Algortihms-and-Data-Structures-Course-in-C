// =================== Support Code =================
// Doubly Linked List ( Team DLL ).SP
//
// - Refer to my_dll.h for the structure definitions.
// - Implement each of the functions to create a working DLL that represents a hockey team.
// - Do not change any of the function declarations
//   - (i.e. team_t* create_team() should not have additional arguments)
// - You should not have any 'printf' statements in your functions.
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc. 0x7E7)
// ==================================================

#include <stdlib.h>
#include <string.h>
#include "my_dll.h" // Include the header file

// Creates a Team
// Returns a pointer to a newly created Team.
// The Team should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The Team fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
team_t* create_team() {
    team_t* team = malloc(sizeof(team_t));
    if (!team) return NULL;
    team->activePlayers = 0;
    team->head = NULL;
    team->tail = NULL;
    return team;
}

// Team DLL Empty
// Check if the team is empty
// Returns -1 if the team is NULL.
// Returns 1 if true (The team is completely empty)
// Returns 0 if false (the team DLL has at least one player enqueued)
int team_empty(team_t* team) {
      if (!team) return -1;
    return team->head == NULL ? 1 : 0;
}

// Function to create a new player
// Returns a pointer to a newly created player.
// The player should be initialized with data on the heap.
player_t* makePlayer(int roster, char* name) {
    player_t* player = malloc(sizeof(player_t));
    if (!player) return NULL;
    player->rosterNum = roster;

   // Allocate memory for the name
    player->name = malloc(strlen(name) + 1); // +1 for null terminator
    if (!player->name) {
        free(player); // Clean up previously allocated memory for the player
        return NULL; // Memory allocation failed for name
    }
    strcpy(player->name, name); // Copy the name

    player->next = NULL;
    player->previous = NULL;
    return player;
}

// push a new player to the front of the DLL ( before the first player in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new player)
// (i.e. the memory allocation for a new player failed).
int team_push_front(team_t* team, int roster, char* name) {
    if (!team) return -1;
    player_t* player = makePlayer(roster, name);
    if (!player) return 0;
    if (!team->head) {
        team->head = player;
        team->tail = player;
    } else {
        player->next = team->head;
        team->head->previous = player;
        team->head = player;
    }
    team->activePlayers++;
    return 1;
}

// push a new player to the end of the team DLL (after the last player in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new player)
// (i.e. the memory allocation for a new player failed).
int team_push_back(team_t* team, int roster, char* name) {
    if (!team) return -1;
    player_t* player = makePlayer(roster, name);
    if (!player) return 0;
    if (!team->tail) {
        team->head = player;
        team->tail = player;
    } else {
        team->tail->next = player;
        player->previous = team->tail;
        team->tail = player;
    }
    team->activePlayers++;
    return 1;
}

// Returns the first player in the DLL and also removes it from the team.
// Returns NULL if the Team is NULL.
// Returns NULL on failure, i.e. there is no one to pop from the team.
// Assume roster numbers are always greater than zero
player_t* team_pop_front(team_t* team) {
    if (!team || !team->head) return NULL;
    player_t* player = team->head;
    team->head = team->head->next;
    if (team->head) {
        team->head->previous = NULL;
    } else {
        team->tail = NULL;
    }
    team->activePlayers--;
    player->next = NULL;
    return player;
}

// Returns the last player in the Team, and also removes it from the list.
// Returns NULL if the Team is NULL.
// Returns NULL on failure, i.e. there is no one to pop from the Team.
// Assume roster numbers are always greater than zero
player_t* team_pop_back(team_t* team) {
    if (!team || !team->tail) return NULL;
    player_t* player = team->tail;
    team->tail = team->tail->previous;
    if (team->tail) {
        team->tail->next = NULL;
    } else {
        team->head = NULL;
    }
    team->activePlayers--;
    player->previous = NULL;
    return player;
}

// Inserts a new player before the player at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new player
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent of calling push_back).
int team_insert(team_t* team, int pos, int roster, char* name) {
    if (!team || pos < 0 || pos > team->activePlayers) return -1;
    if (pos == 0) return team_push_front(team, roster, name);
    if (pos == team->activePlayers) return team_push_back(team, roster, name);

    player_t* newPlayer = makePlayer(roster, name);
    if (!newPlayer) return 0;

    player_t* current = team->head;
    for (int i = 0; i < pos; i++) current = current->next;

    newPlayer->next = current;
    newPlayer->previous = current->previous;
    if (current->previous) current->previous->next = newPlayer;
    current->previous = newPlayer;

    team->activePlayers++;
    return 1;
}

// Returns the roster number of the player at position pos starting at 0
// ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume roster numbers are always greater than zero
int team_list_get(team_t* team, int pos) {
    if (!team || pos < 0 || pos >= team->activePlayers) return -1;

    player_t* current = team->head;
    for (int i = 0; i < pos; i++) current = current->next;

    return current ? current->rosterNum : -1;
}

// Removes the player at position pos starting at 0 ( 0 being the first item )
// Returns NULL if the list is NULL
// Returns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
// Otherwise returns the roster number of the player removed.
player_t* team_list_remove(team_t* team, int pos) {
    if (!team || pos < 0 || pos >= team->activePlayers) return NULL;

    if (pos == 0) return team_pop_front(team);
    if (pos == team->activePlayers - 1) return team_pop_back(team);

    player_t* current = team->head;
    for (int i = 0; i < pos; i++) current = current->next;
    if (current->previous) current->previous->next = current->next;
    if (current->next) current->next->previous = current->previous;

    team->activePlayers--;
    current->next = NULL;
    current->previous = NULL;
    return current;
}

// Team Size
// Returns -1 if the Team is NULL.
// Queries the current size of a team
int team_size(team_t* team) {
    return team ? team->activePlayers : -1;
}

// BONUS function - not required for HW
// no extra credit is given for this function
// Team DLL Sort
// Returns -1 if the Team is NULL.
// sorts the team by roster number, putting the players in order
// with the smallest roster number at the head of the list,
// in ascending order
// only work on this if you're all done with everything else tested!!
void team_sort(team_t* t) {

    // OPTIONAL
}

// Free Team DLL
// Removes a Team and all of its players (...and their names!!...) from memory.
// This should be called before the program terminates.
void free_team(team_t* team) {
    if (!team) return;
    player_t* current = team->head;
    while (current) {
        player_t* next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    free(team);
}
