/****************************
*Author: Ong Ming Hang      *
*Date modified: 25/05/2019  *
****************************/
#ifndef LL_H
#define LL_H
/******************************************************************************
*Purpose: Function pointer to free any struct
*How it works: When dereferenced, it is a function which frees a specific 
*              struct that has been malloc'd
*How it relates: Used in free linked list to effectively free both the data
*                inside the list node and the list node itself
******************************************************************************/
typedef void (*StructKiller)(void*);
/******************************************************************************
*Purpose: Contains the information of a single element inside the linked list
*How it works: Stores any type of data with a next and previous pointer to
*              traverse the linked list
*How it relates: Mostly called inside the linked list to create a new element
*                to be stored
******************************************************************************/
typedef struct Node 
{
    void* data;
    struct Node* next;
    struct Node* prev;
}Node;

/******************************************************************************
*Purpose: Creates a linked list data structure
*How it works: Has a head and tail pointer to keep track of the elements inside
*              the linked list, it does not have any storage capacity limit
*How it relates: Used to store instructions given from adventure files
******************************************************************************/
typedef struct
{
    Node* head;
    Node* tail;
    int count;
}LinkedList;

LinkedList* listCreate (void);
Node* getNewNode(void*);
void insertFirst (void*, LinkedList*);
void* removeLast (LinkedList*);
void freeLinkedList (LinkedList*, StructKiller);
#endif
