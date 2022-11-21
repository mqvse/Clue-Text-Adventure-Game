#include "rooms.h"
#include "items.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//create a array of items
void createItemArray(char* itemNames[], struct Item* newLst[]){
    for(int i = 0; i < 6; i++){
        struct Item* itm = (struct Item*) malloc(sizeof(struct Item));
        itm->name = itemNames[i];
        newLst[i] = itm;
    }
}

//remove item from the item list
struct Item* removeItem(struct Item* itmLst, char* itmName){
    struct Item* itm;

    //item is found at the top of the list
    if(strcmp(itmLst->name, itmName) == 0){
        itm = itmLst;
        itmLst = itmLst->nextItem;
        free(itm);
        return itmLst;
    }

    struct Item* prev = itmLst;
    struct Item* cur = itmLst->nextItem;

    while(strcmp(cur->name, itmName) != 0){
        prev = cur;
        cur = cur->nextItem;
    }

    prev->nextItem = cur->nextItem;
    free(cur);

    return itmLst;
}

//add item to the list
struct Item* addItem(struct Item* itmLst, char* itmName){
    struct Item* newItem = (struct Item*) malloc(sizeof(struct Item));

    newItem->name = itmName;
    newItem->nextItem = itmLst;
    itmLst = newItem;

    return itmLst;
}

//print all items in the list
void printAllItems(struct Item* itmLst){
    if(itmLst == NULL){
        printf("Nothing!!!\n");
    }
    while(itmLst != NULL){
        printf("%s\n", itmLst->name);
        itmLst = itmLst->nextItem;
    }
}

//check if the item is in the item list
bool isFound(struct Item* itmLst, char* itmName){
    bool itemFound = false;
    struct Item* ptr = itmLst;
    while(ptr != NULL){
        if(strcmp(ptr->name, itmName) == 0){
            itemFound = true;
            break;
        }
        ptr = ptr->nextItem;
    }
    return itemFound;
}
