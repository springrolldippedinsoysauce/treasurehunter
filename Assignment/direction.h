/****************************
*Author: Ong Ming Hang      *
*Date modified: 25/05/2019  *
****************************/
#ifndef DIRECTION_H
#define DIRECTION_H
/******************************************************************************
*Purpose: This struct is responsible for storing the direction and number of 
*         steps into a Direction datatype.
*How it works: -
*How it relates: Function advRead will take in the file containing instructions
*                and allocate the memory for this struct so the values is 
*                stored inside this datatype.
*                Function movementProcessor receives a list of Direction struct
*                to be remove from the linked list in order to move the player.
******************************************************************************/
typedef struct
{
    char path[64];
    int step;
}Direction;
#endif
