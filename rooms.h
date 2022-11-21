#include <stdio.h>

//
struct Room {
    char* name;
    struct Room* North;
    struct Room* South;
    struct Room* East;
    struct Room* West;
    struct Item* itemList;
    char* character[6];
};

//swap to Strings s1 and s2
void swapStrings(char** s1, char** s2);

//copy and shuffle the n-length array of strings
void shuffleStrings(char* arr[], char* arr_copy[], int n);

//create a 3x3 grid of rooms and assigned randomly names, items, and chracters into each room
struct Room* createRooms(char* roomNames[], struct Item* itmLst[], char* charNames[], int loc[]);

//print all directions of the rooms
void printAllDirections(struct Room* room);
