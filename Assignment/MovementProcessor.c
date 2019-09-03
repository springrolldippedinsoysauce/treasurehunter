/****************************
*Author: Ong Ming Hang      *
*Program: MovementProcessor *
*Date modified: 25/05/2019  *
****************************/
#include "all_header.h"
/******************************************************************************
*Purpose: Process the 2D array of Treasure struct and linked list to move the
*         character around.
*How it works: Using the linked list to move the player, remove last once 
*              to set the while-loop condition, for every element removed from
*              the list, it checks if the instruction matches any of the
*              conditions, once matched, using a for-loop to move the player
*              one pace at a time and in every for-loop calls itemCollector to
*              collect the items. If the step exceeds the boundary, it will 
*              stop the program and prints "STATUS: FAILED" to the terminal.
*              Else if AI has been defined, for every step stepping out of 
*              boundary, it redirects the step to stop at the edge instead.
*How it relates: Calls function itemCollector to collect item every step of
*                the way.
******************************************************************************/
void movementProcessor (Treasure** itemArr, int row, int col, LinkedList* dir_list)
{
    /**Regex Pattern**
    *"%*c %d-" To read coin.
    *"%*c %[^:]:%d-" To read magic.
    *"%*c %[^:]:%[^:]:%d-" To read gear.
    */
    Direction *grab;
    Equip* player;
    char *path;
    int step, x, y, xloc = 0, yloc = 0, condition = 0;
    player = (Equip*)malloc(sizeof(Equip));
    /*Variable initialisation*/
    player->head = NULL;
    player->chest = NULL;
    player->hands = NULL;
    player->legs = NULL;
    player->headVal = 0;
    player->chestVal = 0;
    player->handsVal = 0;
    player->legsVal = 0;
    player->totalMagic = 0;
    player->totalCoin = 0;
    /*Gets the first node to set condition*/
    grab = (Direction*)removeLast(dir_list);
    /*Write "---" to log file for every new adventure started*/
    #ifdef LOG 
    writeFile("---\n");
    #endif
    while(grab != NULL && condition != 1)
    {
        path = grab->path;
        step = grab->step;
        if(strcmp(capitalizer(path), "UP") == 0)
        {
            #ifdef AI
            if((yloc - step) < 0)
            {
                /*Changes status to CORRECTED*/
                condition = 2;
                /*Redirects step to go to the edge of the map*/
                step = yloc;
                for(y = 0; y < step; y++)
                {
                    itemCollector(itemArr, --yloc, xloc, player);
                }
            }
            else
            {
                for(y = 0; y < step; y++)
                {
                    itemCollector(itemArr, --yloc, xloc, player);
                }
            }
            #else
            if((yloc - step) < 0)
            {
                /*Stops the while loop and change status to FAILED*/
                condition = 1;
                printf("STATUS: FAILED\n");
            }
            else
            {
                for(y = 0; y < step; y++)
                {
                    itemCollector(itemArr, --yloc, xloc, player);
                }
            }
            #endif
        }
        else if(strcmp(capitalizer(path), "DOWN") == 0)
        {
            #ifdef AI
            if((yloc + step) > row - 1)
            {
                /*Changes status to CORRECTED*/
                condition = 2;
                /*Redirects step to go to the edge of the map*/
                step = (row - 1) - yloc;
                for(y = 0; y < step; y++)
                {
                    itemCollector(itemArr, ++yloc, xloc, player);
                }
            }
            else
            {
                for(y = 0; y < step; y++)
                {
                    itemCollector(itemArr, ++yloc, xloc, player);
                }
            }
            #else
            if((yloc + step) > row - 1)
            {
                /*Stops the while loop and change status to FAILED*/
                condition = 1;
                printf("STATUS: FAILED\n");
            }
            else
            {
                for(y = 0; y < step; y++)
                {
                    itemCollector(itemArr, ++yloc, xloc, player);
                }
            }
            #endif
        }
        else if(strcmp(capitalizer(path), "LEFT") == 0)
        {
            #ifdef AI
            if((xloc - step) < 0)
            {
                /*Changes status to CORRECTED*/
                condition = 2;
                /*Redirects step to go to the edge of the map*/
                step = xloc;
                for(x = 0; x < step; x++)
                {
                    itemCollector(itemArr, yloc, --xloc, player);
                }
            }
            else
            {
                for(x = 0; x < step; x++)
                {
                    itemCollector(itemArr, yloc, --xloc, player);
                }
            }
            #else
            if((xloc - step) < 0)
            {
                /*Stops the while loop and change status to FAILED*/
                condition = 1;
                printf("STATUS: FAILED\n");
            }
            else
            {
                for(x = 0; x < step; x++)
                {
                    itemCollector(itemArr, yloc, --xloc, player);
                }
            }
            #endif
        }
        else if(strcmp(capitalizer(path), "RIGHT") == 0)
        {
            #ifdef AI
            if((xloc + step) > col - 1)
            {
                /*Changes status to CORRECTED*/
                condition = 2;
                /*Redirects step to go to the edge of the map*/
                step = (col - 1) - xloc;
                for(x = 0; x < step; x++)
                {
                    itemCollector(itemArr, yloc, ++xloc, player);
                }
            }
            else
            {
                for(x = 0; x < step; x++)
                {
                    itemCollector(itemArr, yloc, ++xloc, player);
                }
            }
            #else
            if((xloc + step) > col - 1)
            {
                /*Stops the while loop and change status to FAILED*/
                condition = 1;
                printf("STATUS: FAILED\n");
            }
            else
            {
                for(x = 0; x < step; x++)
                {
                    itemCollector(itemArr, yloc, ++xloc, player);
                }
            }
            #endif
        }
        /*DO NOT EDIT BEYOND THIS LINE*/
        dirFree(grab);/*Frees the removed nodes*/
        grab = (Direction*)removeLast(dir_list);/*Grabs the next node*/
    }
    /*If no error occurs, displays statistic*/
    if(condition != 1)
    {
        /*When AI is enable and correction occurs*/
        if(condition == 2)
        {
            displayStats(player, "CORRECTED");
        }
        /*Smooth operation, no correction required*/
        else
        {
            displayStats(player, "COMPLETE");
        }
    }
    dirFree(grab);/*Frees the removed node caused by normal version*/
    equipFree(player);/*Free the equipment*/
    /*This line marks the end of an adventure*/
}/*Not too big if its less than 200 lines, pulled a lil sneaky on ya*/

/******************************************************************************
*Purpose: Collect items for the player
*How it works: row and col represents movement and this function is called
*              multiple times to collect each item one pace at a time.
*How it relates: Only called by movementProcessor, it traverses the 2D array of
*                Treasure with existing Treasure structs using a for-loop.
******************************************************************************/
void itemCollector (Treasure** itemArr, int row, int col, Equip* player)
{
    if((itemArr[row][col].type == 'C')||(itemArr[row][col].type == 'c'))
    {
        #ifdef LOG
        char collection[2048];
        printf("COLLECT<ITEM:COINS, XLOC:%d, YLOC:%d, VALUE:%d>\n",
                col, row, itemArr[row][col].coin->value);
        sprintf(collection, "COLLECT<ITEM:COINS, XLOC:%d, YLOC:%d, VALUE:%d>\n",
                col, row, itemArr[row][col].coin->value);
        writeFile(collection);
        #endif
        player->totalCoin += itemArr[row][col].coin->value;
        /*Makes the encountered items to be nothing as it has been collected*/
        itemArr[row][col].type = '-';
    }
    else if((itemArr[row][col].type == 'M')||(itemArr[row][col].type == 'm'))
    {
        #ifdef LOG
        char collection[2048];
        printf("COLLECT<ITEM:MAGIC, XLOC:%d, YLOC:%d, DESCRIPTION:%s, VALUE:%d>\n",
                col, row, itemArr[row][col].magic->detail, 
                itemArr[row][col].magic->value);
        sprintf(collection, "COLLECT<ITEM:MAGIC, XLOC:%d, YLOC:%d, DESCRIPTION:%s, VALUE:%d>\n",
                col, row, itemArr[row][col].magic->detail, 
                itemArr[row][col].magic->value);
        writeFile(collection);
        #endif
        player->totalMagic += itemArr[row][col].magic->value; 
        /*Makes the encountered items to be nothing as it has been collected*/
        itemArr[row][col].type = '-';
    }
    else if((itemArr[row][col].type == 'G')||(itemArr[row][col].type == 'g'))
    {
        /*It's a gear, yeetus function pointer*/
        (*itemArr[row][col].gear->comparePtr)(itemArr[row][col].gear, player, row, col);
        /*Makes the encountered items to be nothing as it has been collected*/
        itemArr[row][col].type = '-';
    }
}

/******************************************************************************
*Purpose: Displays statistic to the terminal
*How it works: Combines all of the value in each gear slot and display 
*              statistic using.
*How it relates: Marks the end of the adventure. Only called when there are
*                no directions left.
******************************************************************************/
void displayStats (Equip* player, char* status)
{
    int totalGear = player->headVal + player->chestVal + player->handsVal +
                    player->legsVal;
    printf("STATUS: %s\n", status);
    printf("GEAR: %d\n", totalGear);
    printf("MAGIC: %d\n", player->totalMagic);
    printf("COIN: %d\n", player->totalCoin);
}

/******************************************************************************
*Purpose: Frees an Equip struct
*How it works: -
*How it relates: Calls it at the end of everything 
*                (e.g. end of movementProcessor).
******************************************************************************/
void equipFree(void* data)
{
    Equip* toFree = (Equip*)data;
    free(toFree);
    toFree = NULL;
}
