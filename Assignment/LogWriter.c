/****************************
*Author: Ong Ming Hang      *
*Program: LogWriter         *
*Date modified: 25/05/2019  *
****************************/
#include "all_header.h"
/******************************************************************************
*Purpose: Writes string to a specific file without overwriting
*How it works: -
*How it relates: Calls when LOG is enable
******************************************************************************/
void writeFile (char* str)
{
    FILE* logFile = fopen ("adventure.log", "a");
    fprintf(logFile, "%s", str);
    fclose(logFile);
}
