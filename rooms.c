#include "rooms.h"
#include "items.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

//swap 2 strings
void swapStrings (char** s1, char** s2){
    char* temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

//shuffle array of strings
void shuffleStrings(char* arr[], char* arr_copy[], int n){
    for(int i = 0; i < n; i++){
        arr_copy[i] = arr[i];
    }

    srand(time(NULL));

    for(int i = n-1; i > 0; i--){
        int j = rand() % (i + 1);
        swapStrings(&arr_copy[i], &arr_copy[j]);
    }
}    

//initialize rooms
struct Room * createRooms(char* roomNames[], struct Item* itmLst[], char* charNames[], int loc[]){
    struct Room* p = (struct Room*) malloc(9 * sizeof(struct Room));

    for (int i = 0; i < 9; i++){
        (p+i) -> North = i < 3          ? NULL : (p + i - 3);
        (p+i) -> South = i > 5          ? NULL : (p + i + 3);
        (p+i) -> West  = (i % 3 == 0)   ? NULL : (p + i - 1);
        (p+i) -> East  = (i % 3 == 2)   ? NULL : (p + i + 1);

        (p+i) -> character[0] = "empty";
        (p+i) -> name = roomNames[i];       
    }

    for(int i = 0; i < 6;i++){
       (p+8-i)->character[0] = charNames[i];
       loc[i] = 8-i;
       (p+i)->itemList = itmLst[i];
    }

    return p;
}

//prints all directions of the room
void printAllDirections(struct Room* room){
    if(room->East == NULL){
        printf("East: No entry\n");
    } else {
        printf("East: %s\n", room->East->name);
    }
    if(room->West == NULL){
        printf("West: No entry\n");
    } else {
        printf("West: %s\n", room->West->name);
    }
    if(room->North == NULL){
        printf("North: No entry\n");
    } else {
        printf("North: %s\n", room->North->name);
    }
    if(room->South == NULL){
        printf("South: No entry\n");
    } else {
        printf("South: %s\n", room->South->name);
    }
}