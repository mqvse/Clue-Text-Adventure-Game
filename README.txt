Clue Game

1. 
There are 5 files, which are items.h, items.c, rooms.h, rooms.c, and adventure.c.
items.h and rooms.h are header files, where Room and Item structs and most of functions are defined.
items.c and rooms.c are where the functions are implemented.
adventure.c contains the main function of the project. 
To start the project, in terminal, type: gcc items.h items.c rooms.h rooms.c adventure.c -o adventure.
Then the user is asked to enter 8 commands, help, list, look, go, take, drop, inventory, and clue.
When enter one of 4 following commands: go, take, drop, and clue, the user is asked to enter another command like direction to go, item to take, item to drop, and guessing character, respectively.
If the user type the command that are not in these commands, the user have to retype.
To win the game, the user must be in the correct room, have the correct item in the inventory, and guess the correct character within 10 attemps by using only 8 above commands.

2.
At the start of the game, 9 rooms are assigned in to a 3x3 table/grid.
Each room is randomly assigned a name, 4 direction pointers (North, South, East, West), 1 linked list of items, and an array of characters.
Every room is connected to the others through direction pointers if they are adjacent.
If the room are on the topmost of the board, the North pointer is pointing to NULL.
If the room are on the bottommost of the board, the South pointer is pointing to NULL.
If the room are on the rightmost of the board, the East pointer is pointing to NULL.
If the room are on the leftmost of the board, the West pointer is pointing to NULL.
The user will be assigned to a random room by pointer p
During the game, the user can move to other room with the pointer by command go.

3. 
The user can only use 8 commands by typing "help", "list", "look", "go", "take", "drop", "inventory", and "clue".
If the user type incorrectly (the uppercase and lowercase letters cannot be interchanged).
After typing the command, the program will use getline and strcmp to recognize the user's commands and call the correct functions.
To do the command help, the function help() is called and all the commands are printed to the terminal.
To do the command list, the function list() is called and all the rooms, items, and characters are printed out.
To do the command look, the function look() is called and the name of current room, all items, and characters in the room are printed out.
To do the command go, the user is asked to type the direction ("North", "South", "East", "West"), the function go is called and the pointer points to the room in that direction.
If the direction is invalid, the user have to retype.
To do the command take, the user is asked to type the item to take, the function removeItem() is called to remove the item from the room, then the function addItem() is called to add the item to the inventory.
To do the command drop, the user is asked to type the item to drop, the function removeItem() is called to remove the item from the inventory, then the function addItem() is called to add the item to the room.
To do the command inventory, the function inventory() is called and all the items in the inventory is printed out.
To do the command take, the user is asked to type the guessing character.
If the user are in the correct room, the room or inventory contains the correct item, and the user guess the correct character, the user won.
If the user types incorrect character or is in the incorrect room or the room or inventory doesn't contain the correct item, the user will lose 1 attemp.
There are only 10 attemps.
If the user type a character that are not in the list of chracter, the user have to retype and the user won't lose any attemps.
If the attemp is 0. The user will lose.