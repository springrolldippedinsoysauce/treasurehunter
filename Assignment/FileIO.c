/****************************
*Author: Ong Ming Hang      *
*Program: FileIO            *
*Date modified: 25/05/2019  *
****************************/
#include "all_header.h"
#define MAX_STR_LEN 512

/******************************************************************************
*Purpose: Converts original map into a readable map
*How it works: Opens the map file and reads character by character, for every
               comma or new line, it adds a dash to signify spaces
*How it relates: Onces formatted, the function mapRead will be forced to take 
*                in the formatted file.
******************************************************************************/
int mapFormat (char* map)
{
    FILE* inFile;
    FILE* outFile;
    char ch;
    int status;
    ch = '\0';
    status = 0;
    inFile = fopen(map, "r");
    if(inFile == NULL)
    {
        perror("Error opening file");
        printf("File name: [%s]\n", map);
    }
    else
    {
        outFile = fopen("map_format.txt", "w");
        do
        {
            ch = fgetc(inFile);
            if(ch != EOF)
            {
                /*For every comma it encounters, place a dash*/
                if((char)ch == ',')
                {
                    fputc('-', outFile);
                }
                /*For every new line character it encounters, place a dash*/
                if((char)ch == '\n')
                {
                    fputc('-', outFile);
                }
                fputc((char)ch, outFile);       
            }
        }while(ch != EOF);
        fclose(inFile);
        fclose(outFile);
        status = 1;
    }
    /**************************************************************************
    *Status prevents mapRead from reading the format map when it returns 0, 
    *else read when 1 is returned, just means that the file is A-OK
    **************************************************************************/
    return status;
} 

/******************************************************************************
*Purpose: Reads a file into a Direction struct which is then stored inside a
*         generic linked list.
*How it works: Using feof function, while it is not the end-of-file, malloc
*              Direction struct to be stored with file contents and inserted
*              into the generic linked list.
*How it relates: Once the instruction has been stored, it is then pass by
*                reference into movementProcessor which is removed in
*                first-in-last-out order.
******************************************************************************/
int advRead (char* adventure, LinkedList* dir_list)
{
    Direction *direction;
    FILE* inFile = fopen(adventure, "r");
    int status = 0, isCorrect = 0, stop = 0;
    if(inFile == NULL)
    {
        perror("Error opening file");
        printf("File name: [%s]\n", adventure);
    }
    else
    {
        while(!feof(inFile) && stop != 1)
        {
            /*For every line inside the file, malloc and store the contents*/
            direction = (Direction*)malloc(sizeof(Direction));
            isCorrect = fscanf(inFile, "%s %d\n", direction->path, &direction->step);
            /*If the contents being scanned is correct, insert into list*/
            if(isCorrect == 2 || direction->step >= 0)
            {
                insertFirst(direction, dir_list);
            }
            /*Stop reading and free the unwanted content*/
            else
            {
                stop = 1;
                dirFree(direction);
                printf("Error: Invalid move command\n");
            }
        }
        fclose(inFile);
        if(stop != 1)
        {
            status = 1;
        }
        else
        {
            status = 0;
        }
    }
    /**************************************************************************
    *Status prevents mapRead from reading the format map when it returns 0, 
    *else read when 1 is returned, just means that the file is A-OK
    **************************************************************************/
    return status;
}

/******************************************************************************
*Purpose: Convert the csv file into a 2D array of Map struct
*How it works: Starts by grabbing the first line on each file to find rows and
*              columns, once that is done it will proceed to grab the number of
*              lines from the file to validate the number of rows. If it is 
*              validated, proceed to store the contents of the map via string 
*              tokenizer into the allocated 2D array of Map struct. Freeing 
*              everything before the function ends.
*How it relates: It is passed into function itemProcessor to convert a 2D 
*                array of Map struct to a 2D array of Treasure struct.
******************************************************************************/
void mapRead (char* map, LinkedList* dir_list)
{
    FILE* formatFile = fopen(map, "r");
    FILE* formatLine = fopen(map, "r");
    char line [128];
    char size [20];
    int row, col, i = -1, j = -1, line_count = -1, isCorrect = -1;
    Map **mapArr;
    char* tok;
    if(formatFile == NULL)
    {
        perror("Error opening file");
        printf("File name: [%s]\n", map);
    }
    else
    {
        /*If it isn't empty, read*/
        if(fgets(size, sizeof(line), formatFile) != NULL)
        {
            isCorrect = sscanf(size, "%d-,%d-", &row, &col);
            if(isCorrect == 2)
            {
                /*Memory allocation for map*/
                mapArr = (Map**)malloc(sizeof(Map*) * row);
                for (i = 0; i < row; i++)
                {
                    mapArr[i] = (Map*)malloc(sizeof(Map) * col);
                }
                /*End of memory allocation*/     
                line_count = getNumLines(formatLine);
                /*Stops the program as the row provided by the map is incorrect*/
                if(row != line_count - 1)
                {
                    printf("Error: Lines do not conform to the specified structure\n");
                    printf("STATUS: ABORTED\n");
                }
                else
                {
                    for(i = 0; i < row; i++)
                    {
                        j = 0;/*resets j to zero, based on zero index array*/
                        fgets(line, sizeof(line), formatFile);/*Gets the line*/
                        tok = strtok(line, ",");
                        while(tok != NULL)
                        {
                            /*Fills the 2D array with map information*/
                            strncpy(mapArr[i][j].item_name, tok, 128);
                            /*READS the next item on the row after encountering comma*/
                            tok = strtok(NULL, ",");
                            j++;
                        }
                    }
                    /*Converts into 2D array of Treasure struct*/
                    itemProcessor(mapArr, row, col, dir_list);
                }
                /*Freeing dynamically allocated array*/
                for (i = 0; i < row; i++)
                {
                    free(mapArr[i]);
                    mapArr[i] = NULL;
                }
                free(mapArr);
                mapArr = NULL; 
            }
            else
            {
                printf("Error: Rows and columns not specified!\n");
                printf("STATUS: ABORTED\n");
            }
        }
        else
        {
            printf("Error: File is empty!\n");
            printf("STATUS: ABORTED\n");
        }
        fclose(formatFile);
        fclose(formatLine);
    } 
} 

/******************************************************************************
*Purpose: Gets the number of lines from a file pointer
*How it works: Grabs each character from the file, when it hits a new line
*              character, increments the line_count by 1. Returns the count.
*How it relates: Used to validate rows in function mapRead
******************************************************************************/
int getNumLines(FILE* file)
{
    int line_count = 0;
    char ch = '\0';
    ch = fgetc(file);
    do
    {
        /*When it hits a new line character*/
        if((char)ch == '\n')
        {
            line_count++;
        }
        ch = fgetc(file);
    }while(ch != EOF);
    return line_count;
}

/******************************************************************************
*Purpose: Frees a Direction struct
*How it works: -
*How it relates: Called in main to free any remainding Direction struct and
*                in movementProcessor to free any used Direction struct.
******************************************************************************/
void dirFree (void* data)
{
    Direction* dir = (Direction*)data; 
    free(dir);
    dir = NULL;
}

