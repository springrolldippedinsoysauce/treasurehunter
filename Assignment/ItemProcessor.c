/****************************
*Author: Ong Ming Hang      *
*Program: ItemProcessor     *
*Date modified: 25/05/2019  *
****************************/
#include "all_header.h"
/******************************************************************************
*Purpose: Converts the 2D array of Map struct into 2D array of treasure struct
*How it works: Takes in the 2D array Map struct alongside with correct rows 
*              and columns, also a generic linked list. Allocate the memory
*              required and it is then stored into the newly allocated 2D
*              array of Treasure using sscanf to read from full string into 
*              different sets of variables located inside Treasure struct.
*How it relates: Once the new map is set, it is then passed into the function
*                movementProcessor where it will be able to move the 
*                character around.
******************************************************************************/
void itemProcessor (Map** mapArr, int row, int col, LinkedList* dir_list)
{
    Treasure** treasure;
    int i, j, isCorrect = 0;
    /*Memory Allocation*/ 
    treasure = (Treasure**)malloc(sizeof(Treasure*) * row);
    for(i = 0; i < row; i++)
    {
        treasure[i] = (Treasure*)malloc(sizeof(Treasure) * col);
    }   
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            treasure[i][j].gear = (Gear*)malloc(sizeof(Gear));         
            treasure[i][j].magic = (Magic*)malloc(sizeof(Magic)); 
            treasure[i][j].coin = (Coin*)malloc(sizeof(Coin));
        }
    }
    /*End of memory allocation*/
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            sscanf(mapArr[i][j].item_name, "%c ", &treasure[i][j].type); 
            if((treasure[i][j].type == 'C')||(treasure[i][j].type == 'c'))
            {
                isCorrect = sscanf(mapArr[i][j].item_name, "%c %d-", 
                                   &treasure[i][j].coin->type, 
                                   &treasure[i][j].coin->value);
                /*Contents with invalid format is render as worthless*/
                if(treasure[i][j].coin->value < 0 || isCorrect != 2)
                {
                    treasure[i][j].type = '-';
                }
            }                 
            else if((treasure[i][j].type == 'M')||(treasure[i][j].type == 'm'))
            {
                /*Regex pattern %[^:] is defined as "read until you hit a ':'*/
                isCorrect = sscanf(mapArr[i][j].item_name, "%c %[^:]:%d-",
                                   &treasure[i][j].magic->type,
                                   treasure[i][j].magic->detail,
                                   &treasure[i][j].magic->value);
                /*Contents with invalid format is render as worthless*/
                if(treasure[i][j].magic->value < 0 || isCorrect != 3)
                {
                    treasure[i][j].type = '-';
                }
            }                 
            else if((treasure[i][j].type == 'G')||(treasure[i][j].type == 'g'))
            {
                /*Regex pattern %[^:] is defined as "read until you hit a ':'*/
                isCorrect = sscanf(mapArr[i][j].item_name, "%c %[^:]:%[^:]:%d-",
                                   &treasure[i][j].gear->type,
                                   treasure[i][j].gear->detail,
                                   treasure[i][j].gear->slot,
                                   &treasure[i][j].gear->value);
                /*Contents with invalid format is render as worthless*/
                if(treasure[i][j].gear->value < 0 || isCorrect != 4)
                {
                    treasure[i][j].type = '-';
                }
                else
                {
                    /*Within each gear tile on the new map lies a function pointer*/
                    if(strcmp(capitalizer(treasure[i][j].gear->slot), "HEAD") == 0)  
                    {
                        treasure[i][j].gear->comparePtr = &compareHead; 
                    }                                                           
                    else if(strcmp(capitalizer(treasure[i][j].gear->slot), "CHEST") == 0)        
                    {                                                           
                        treasure[i][j].gear->comparePtr = &compareChest; 
                    }                                                           
                    else if(strcmp(capitalizer(treasure[i][j].gear->slot), "HANDS") == 0)    
                    {           
                        treasure[i][j].gear->comparePtr = &compareHands; 
                    }                                                           
                    else if(strcmp(capitalizer(treasure[i][j].gear->slot), "LEGS") == 0)      
                    {                                                           
                        treasure[i][j].gear->comparePtr = &compareLegs; 
                    }
                } 
            }                 
        }
    }
    /*Passed to move the player around*/
    movementProcessor(treasure, row, col, dir_list);
    /*Freeing dynamically allocated memory*/
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            free(treasure[i][j].gear);
            treasure[i][j].gear = NULL;

            free(treasure[i][j].magic);
            treasure[i][j].magic = NULL;

            free(treasure[i][j].coin);
            treasure[i][j].coin = NULL;
        }
        free(treasure[i]);
        treasure[i] = NULL;
    }
    free(treasure);
    treasure = NULL;
}

/******************************************************************************
*Purpose: Switches any lowercase to uppercase and returns the new string
*How it works: Check each and every character of the string parameter and check
*              if any character is larger than 'Z' in terms of ASCII values is
*              subtracted with 32 to get the uppercase character. It is then
*              combined into a new string.
*How it relates: For words like 'cHeSt', the conditions should be able to 
*                detect it regardless of its cases.
******************************************************************************/
char* capitalizer (char* parameter)
{
    int i, len;
    char charArr[512];
    len = strlen(parameter);
    for(i = 0; i < len; i++)
    {
        charArr[i] = parameter[i];
        if(charArr[i] > 'Z')
        {
            parameter[i] = charArr[i] - 32;
        }
    }
    return parameter;
}
