#include "items.h"
#include "rooms.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//print all the commands
void help(){
    printf("All of the commands that you have are:\n");
    printf("1. help\n");
    printf("2. list\n");
    printf("3. look\n");
    printf("4. go\n");
    printf("5. take\n");
    printf("6. drop\n");
    printf("7. inventory\n");
    printf("8. clue\n");
}

//print all rooms, items, and characters
void list(char * cArr[], char * iArr[], char * rArr[]) {
    printf("Item list:\n");
    int i = 0;
    while(i < 6){
        printf("%s ", iArr[i]);
        i++;
    }
    printf("\n");

    printf("Room list:\n");
    i = 0;
    while(i < 9){
        printf("%s ", rArr[i]);
        i++;
    }
    printf("\n");

    printf("Charater list:\n");
    i = 0;
    while(i < 6){
        printf("%s ", cArr[i]);
        i++;
    }
    printf("\n");
}

//print name of current room, all directions, chracters and items that are in the room
void look(struct Room* p) {
    //print name of the room
    printf("You are in the %s\n", p->name);

    //print rooms in all directions
    printAllDirections(p);

    //print all characters who are in the room
    if(strcmp(p->character[0], "empty") == 0){
        printf("There is no one in this room\n");
    } else {
        int i = 0;
        printf("Characters in this room:\n");
        while(p->character[i] != NULL) {
            if(strcmp(p->character[i], "isRemoved") != 0){
                printf("%s\n", p->character[i]);
            }
            i++;
        }
    }

    //print itemList
    printf("This room contains:\n");
    printAllItems(p->itemList);
}

//Move the pointer to the correct direction
struct Room* go(struct Room* p, char* direction){
    if(strcmp(direction, "North") == 0){
        if(p->North == NULL){
            printf("You can't go this way!\n");
        } else {
            p = p->North;
        }
    } else if (strcmp(direction, "South") == 0){
        if(p->South == NULL){
            printf("You can't go this way!\n");
        } else {
            p = p->South;
        }
    } else if (strcmp(direction, "East") == 0){
        if(p->East == NULL){
            printf("You can't go this way!\n");
        } else {
            p = p->East;
        }
    } else if (strcmp(direction, "West") == 0){
        if(p->West == NULL){
            printf("You can't go this way!\n");
        } else {
            p = p->West;
        }
    } else {
        printf("Invalid direction!\n");
    }
    return p;
}

//print all the items in the inventory
void inventory(struct Item* invntry) {
    printf("Your inventory has:\n");
    printAllItems(invntry);
}


//--------------------------------------------------//


int main() { 
    char* roomNames[9] = {"Lederle", "Library", "Modrill", "Flint Lab", "ILC", "Worc DC", "Hamp DC", "Berk DC", "Frank DC"};
    char* itemNames[6] = {"Book", "Pen", "Pencil", "Ruler", "Marker", "Eraser"};
    char* charNames[6] = {"Ann", "Bob", "Camila", "David", "Ethan", "Felix"};

    //location of characters
    int location[6] = {-1,-1,-1,-1,-1,-1};

    //shuffle rooms
    char* roomNames_copy[9];
    shuffleStrings(roomNames, roomNames_copy, 9);

    //shuffle items
    char* itemNames_copy[6];
    shuffleStrings(itemNames, itemNames_copy, 6);
    struct Item* itmArray[6];
    createItemArray(itemNames_copy, itmArray);

    //shuffle characters
    char* charNames_copy[6];
    shuffleStrings(charNames, charNames_copy, 6);

    printf("Welcome to Clue!\n");

    srand(time(0));
    //create a game board
    struct Room* r = createRooms(roomNames_copy, itmArray, charNames_copy, location);
    struct Room* p = r + (rand() % 9);

    //create an inventory
    struct Item* invntry;

    //set the answers
    srand(time(NULL));
    char* ROOM_ANSWER = roomNames[rand()%9];
    char* ITEM_ANSWER = itemNames[rand()%6];
    char* CHARACTER_ANSWER = charNames[rand()%6];

    //initialize attemps and flag to check winning state
    int attemps = 10;
    bool win = false;

    //initialize string for user's input
    size_t textSize = 32;
    char* text = (char*) malloc(textSize*sizeof(char));
    size_t characters;

    while(attemps > 0){
        printf("Enter \"help\" to see all of the commands\n");
        printf("Please enter a command: ");
        characters = getline(&text, &textSize, stdin);
        text[strlen(text)-1] = '\0';

        //call the correct user's command or ask user to retype if incorrect command
        if(strcmp(text, "help") == 0){ 
            help();
        } 
        else if(strcmp(text, "list") == 0){
            list(charNames, itemNames, roomNames); 
        } 
        else if(strcmp(text, "look") == 0){ 
            look(p);
        } 
        else if(strcmp(text, "go") == 0){ 
            printf("Please enter the direction that you want to go: ");
            characters = getline(&text, &textSize, stdin);
            text[strlen(text)-1] = '\0';

            p = go(p, text); 
        } 
        else if(strcmp(text, "take") == 0){
            char* newText1 = (char*) malloc(textSize*sizeof(char));
            size_t newCharacters1;

            printf("Please enter the item that you want to take: ");
            newCharacters1 = getline(&newText1, &textSize, stdin);
            newText1[strlen(newText1)-1] = '\0';

            bool itemFound = isFound(p->itemList, newText1);

            //If this item is not in this room -> retype
            if(!itemFound){
                printf("%s is not in this room\n", newText1);
            } else {
                //remove item from the room and add it to the inventory
                p->itemList = removeItem(p->itemList, newText1);
                invntry = addItem(invntry, newText1);
            }

        } else if(strcmp(text, "drop") == 0){ 
            char* newText2 = (char*) malloc(textSize*sizeof(char));
            size_t newCharacters2;

            printf("Please enter the item that you want to drop: ");
            newCharacters2 = getline(&newText2, &textSize, stdin);
            newText2[strlen(newText2)-1] = '\0';

            bool itemFound = isFound(invntry, newText2);

            //If this item is not in the inventory -> retype
            if(!itemFound){
                printf("%s is not in your inventory\n", newText2);
            } else {
                //remove item from inventory and add it to the room
                invntry = removeItem(invntry, newText2);
                p->itemList = addItem(p->itemList, newText2);
            }

        } 
        else if(strcmp(text, "inventory") == 0){ 
            inventory(invntry);
        } 
        else if(strcmp(text, "clue") == 0){
            int score = 0;

            char* newText3 = (char*) malloc(textSize*sizeof(char));
            size_t newCharacters3;

            printf("The correct character is: ");
            newCharacters3 = getline(&newText3, &textSize, stdin);
            newText3[strlen(newText3)-1] = '\0';

            //check if the input character is valid
            bool is_valid_char = false;
            for(int i = 0; i < 6; i++){
                if(strcmp(newText3, charNames[i]) == 0){
                    is_valid_char = true;
                    break;
                }
            } 

            if(is_valid_char){
                //show whether the character input is correct
                if(strcmp(CHARACTER_ANSWER, newText3) == 0){
                    printf("Character %s is correct!\n", CHARACTER_ANSWER);
                    score++;
                } else { printf("Character %s is incorrect!\n", newText3); }

                int room_number;
                //find room number in location array
                int i = 0;
                while(i < 6){
                    if(strcmp(charNames_copy[i], newText3)==0){
                        room_number = location[i];

                        //update location array
                        location[i] = -1;
                        break;
                    }
                    i++;
                }

                //remove this character from this room
                int j = 0;
                while((r+room_number)->character[j] != NULL){
                    if(strcmp((r+room_number)->character[j], newText3)){
                        (r+room_number)->character[j] = "isRemoved";
                        break;
                    }
                    j++;
                } 

                //add charater to the current room
                int k = 0;
                while(p->character[k] != NULL && strcmp(p->character[k], "isRemoved") != 0){
                    k++;
                }
                p->character[k] = newText3;

                //update location array
                int l = 0;
                while(l < 9){
                    if(strcmp(roomNames_copy[l], p->name) == 0){
                        location[i] = l;
                        break;
                    }
                    l++;
                }

                //show whether the room input is correct
                if(strcmp(ROOM_ANSWER, p->name) == 0){
                    printf("You are in the correct place! It's %s.\n", ROOM_ANSWER);
                    score++;
                } else { printf("You are in a wrong place!\n"); }

                //show whether the item input is correct
                if(isFound(invntry, ITEM_ANSWER) || isFound(p->itemList, ITEM_ANSWER)){
                    printf("%s is the correct item\n", ITEM_ANSWER);
                    score++;
                } else { printf("The correct item isn't in this room nor in your inventory!\n"); }

                //show number of correct answers
                printf("You got %d/3 correct answers!\n", score);

                //if all 3 answers are correct => change flag to win and break loop 
                if(score == 3){
                    win = true;
                    break;
                }

                attemps--;
                printf("You have %d attemps left!\n", attemps);

            } else {
                printf("%s doesn't exist!!!\n", newText3);
                printf("You have %d attemps left!\n", attemps);
            }

        } else { 
            printf("Invalid command!\n");
        }
    }

    if(!win){
        printf("GAME OVER!\n");
    } else {
        printf("YOU WON!!!\n");
    }

    free(text);
    free(r);
    
    return 0;
}
