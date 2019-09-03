/****************************
*Author: Ong Ming Hang      *
*Date modified: 25/05/2019  *
****************************/
#ifndef FILEIO_H
#define FILEIO_H
/******************************************************************************
*Purpose: Stores the file content into a Map struct
*How it works: -
*How it relates: The map processor will translate file content into string and
*                store it as a Map struct
******************************************************************************/
typedef struct
{
    char item_name[2048];
}Map;
int mapFormat (char*);
int advRead (char*, LinkedList*);
void mapRead (char*, LinkedList*);
int getNumLines(FILE*);
void dirFree (void* data);
#endif
