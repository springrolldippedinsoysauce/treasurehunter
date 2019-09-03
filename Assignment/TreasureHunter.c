/****************************
*Author: Ong Ming Hang      *
*Program: TreasureHunter    *
*Date modified: 25/05/2019  *
****************************/
#include "all_header.h"
/******************************************************************************
*Purpose: Takes command-line arguments to be passed into reading functions
*How it works: Grabs command-line from the terminal and toss into functions
*How it relates: The core of the program where it initialises the other 
*                functions to read, collect and display.
******************************************************************************/
int main (int argc, char** argv)
{
    int choice, map_status = 0, adv_status = 0;
    LinkedList *dir_list;
    /*Function pointer which takes in type*/
    StructKiller dir_free_ptr;
    /*If the format is ./TreasureHunter [map] [adventure] then it continues*/
    if(argc == 3)
    {
        /*Creates a linked list for direction storage*/
        dir_list = listCreate();
        /*If the number of argument is correct, prints the welcome message*/
        printf("Welcome to Treasure Hunter!\n");
        do
        {
            printf("Select one of the option:\n1. Start game\n2. Exit\n");
            printf("User input: ");
            scanf("%d", &choice);
            switch (choice)
            {
                case 1:
                    printf("Game started!\n");
                    /*
                     *Both functions return an int, if it is 0 means that an
                     *error ocurred in either function and it won't initiate 
                     *map creation and direction storage
                     */
                    /*Reformats the map*/
                    map_status = mapFormat(argv[1]); 
                    adv_status = advRead(argv[2], dir_list);
                    if(map_status != 0 && adv_status != 0)
                    {
                        /*Force the program to pass in the formatted file*/
                        mapRead("map_format.txt", dir_list);
                    }
                    break;
                case 2: 
                    printf("...Exiting Treasure Hunter...\n");
                    break;
                default:
                    printf("Invalid Option! Try again!\n");
                    break;
            }
        /*While player doesn't want to end the game, loops*/
        }while(choice != 2);
        /*Frees the Direction struct linked list and it's malloc*/
        dir_free_ptr = &dirFree;
        freeLinkedList(dir_list, dir_free_ptr);
    }
    else
    {
        /*Stops the program and prints message*/
        printf("Error: Invalid number of input argument!\n");
    }
    return 0;
}

