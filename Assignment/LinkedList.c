/****************************
*Author: Ong Ming Hang      *
*Program: LinkedList        *
*Date modified: 25/05/2019  *
****************************/
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/******************************************************************************
*Purpose: Creates an empty linked list
*How it works: Malloc'd the linked list once and returns it
*How it relates: Used to store instructions from adventure
******************************************************************************/
LinkedList* listCreate ()
{
    LinkedList* newList;
    newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->count = 0;
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

/******************************************************************************
*Purpose: Creates a new node containing information
*How it works: Malloc'd the list node once and returns it
*How it relates: Called multiple times as more element is stored into the list,
*                there is no limit to for many it can store
******************************************************************************/
Node* getNewNode(void* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/******************************************************************************
*Purpose: Insert first onto the list
*How it works: When a node is added into an existing linked list structure, 
*              starts by getting the current head previous pointer to point at
*              the new node and have the new node next pointer to point at the
*              current head, then the list head pointer now points to the new
*              node and the new node previous pointer points to nothing
*How it relates: Used to stored direction in FILO (first-in-last-out) order
******************************************************************************/
void insertFirst (void* data, LinkedList* list)                                   
{                                                                           
    Node* newNode = getNewNode(data);
    /*If there is no head, new node is now the new head and tail*/
    if (list->head == NULL)                                                          
    {                                                                       
        list->head = newNode;               
        list->tail = newNode;
    }
    /*Else if there is an existing linked list structure, insert and rebalance*/
    else
    { 
        list->head->prev = newNode;/*Current head previous pointer points to newNode*/
        newNode->next = list->head;/*newNode next pointer points to current head*/
        list->head = newNode;/*List now has a new head, which is the newNode*/
        list->head->prev = NULL;/*newNode previous pointer points to NULL*/
    }                           
    list->count++;/*New element*/   
}   

/******************************************************************************
*Purpose: Remove last element from the linked list
*How it works: Using the existing linked list, remove the last element and
*              depends on three cases which are if the list is empty, list has
*              only one element and list has more than one element. When called
*              , if the list is empty just return NULL, else if there is only
*              one element in the list, store the tail into temp, grabs the
*              data from temp, makes the list head and tail points to NULL and
*              frees temp which is the lost tail pointer. Else if there is more
*              than one element in the list, store the tail into temp, grabs
*              the data from temp, makes the list tail previous pointer to 
*              point at the previous element and set the current tail next 
*              pointer to remove the reference to previous tail, frees temp 
*              which is the lost tail pointer.
*How it relates: Used to remove direction in FILO (first-in-last-out) order
******************************************************************************/
void* removeLast (LinkedList* list)
{
    void* data = NULL; 
    Node* temp;
    if(list->head == NULL)
    { 
        data = NULL;/*List is empty, return NULL*/
    }
    else if (list->count == 1)
    {
        temp = list->tail;/*temp now has a reference to the current tail*/
        data = temp->data;/*Grabs the data from temp*/
        list->head = NULL;/*Points to NULL because it is empty*/
        list->tail = NULL;/*Points to NULL because it is empty*/
        free(temp);/*Frees the lost reference of tail pointer*/
        list->count--;/*Removed element*/
    }
    else
    {
        temp = list->tail;/*temp now has a reference to the current tail*/
        data = temp->data;/*Grabs the data from temp*/
        list->tail = list->tail->prev;/*List tail now points to a new tail*/
        list->tail->next = NULL; /*Current tail next pointer points to NULL*/
        free(temp);/*Frees the lost reference of tail pointer*/
        list->count--;/*Removed element*/
    }
    return data;
}

/******************************************************************************
*Purpose: Frees a linked list and malloc'd struct
*How it works: Grabs the head to set a condition for the while-loop, while 
*              there exist some data, make nextNode to point at the next 
*              element of node, frees the malloc'd data inside node and frees
*              the node itself, node now points at the next element, continue
*              loop until there is nothing left.
*How it relates: Used to free any remaining instructions that weren't used in
*                the linked list, occurs at the end of the entire program.
******************************************************************************/
void freeLinkedList (LinkedList* list, StructKiller sk)
{
    Node *node, *nextNode;
    node = list->head;/*Sets the condition for the while-loop*/
    while (node != NULL)
    {
        nextNode = node->next;/*nextNode has a reference to node*/
        (*sk)(node->data);/*Frees the malloc'd data inside node*/
        free(node);/*Free the node itself*/
        node = nextNode;/*Iterates until it hits NULL*/
    }
    free(list);/*Frees the linked list*/   
}

