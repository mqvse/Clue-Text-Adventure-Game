#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Item {
    char* name;
    struct Item* nextItem;    
};

//create a struct Item* array from array of item names
void createItemArray(char* itemNames[], struct Item* newLst[]);

//remove the item that has the same name as itmName from the linked list
struct Item* removeItem(struct Item* itmLst, char * itmName);

//add an item that has the same name as itmName from the linked list
struct Item* addItem (struct Item* itmLst, char* itmName);

//print all the items in the itmLst
void printAllItems(struct Item* itmLst);

//check if the item that has the same name as itmName is in the linked list
bool isFound(struct Item* itmLst, char* itmName);
