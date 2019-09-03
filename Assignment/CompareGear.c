/****************************
*Author: Ong Ming Hang      *
*Program: CompareGear       *
*Date modified: 25/05/2019  *
****************************/
#include "all_header.h"
/******************************************************************************
*Purpose: Compares current head equipment with new head equipment
*How it works: Swaps the current head equipment if it is weaker than the new 
*              head equipment, else if there is no head equipment, wear it.
*How it relates: Called on through function pointer located inside gear struct
******************************************************************************/
void compareHead (Gear* newHead, Equip* equipped, int yloc, int xloc)
{
    #ifdef LOG
    char collect[2048];
    char discard[2048];
    #endif 
    /*If the slot is empty, just equip it*/
    if(equipped->head == NULL)
    {
        /*Equip into empty slot*/
        equipped->head = newHead;
        equipped->headVal = newHead->value;
        #ifdef LOG
        printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->head->detail, equipped->head->slot, 
                equipped->head->value);
        sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->head->detail, equipped->head->slot, 
                equipped->head->value);
        writeFile(collect);
        #endif
    }
    else
    {
        if(equipped->head->value < newHead->value)
        {
            #ifdef LOG
            printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newHead->detail, newHead->slot, 
                    newHead->value);
            sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newHead->detail, newHead->slot, 
                    newHead->value);
            writeFile(collect);
            printf("DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->head->detail, equipped->head->slot, 
                    equipped->head->value);
            sprintf(discard, "DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->head->detail, equipped->head->slot, 
                    equipped->head->value);
            writeFile(discard);
            #endif
            /*Equip the better item*/
            equipped->head = newHead;
            equipped->headVal = newHead->value;
        }
    }
}

/******************************************************************************
*Purpose: Compares current chest equipment with new chest equipment
*How it works: Swaps the current chest equipment if it is weaker than the new 
*              chest equipment, else if there is no chest equipment, wear it.
*How it relates: Called on through function pointer located inside gear struct
******************************************************************************/
void compareChest (Gear* newChest, Equip* equipped, int yloc, int xloc)
{
    #ifdef LOG
    char collect[2048];
    char discard[2048];
    #endif 
    /*If the slot is empty, just equip it*/
    if(equipped->chest == NULL)
    {
        /*Equip into empty slot*/
        equipped->chest = newChest;
        equipped->chestVal = newChest->value;
        #ifdef LOG
        printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->chest->detail, equipped->chest->slot, 
                equipped->chest->value);
        sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->chest->detail, equipped->chest->slot, 
                equipped->chest->value);
        writeFile(collect);
        #endif
    }
    else
    {
        if(equipped->chest->value < newChest->value)
        {
            #ifdef LOG
            printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newChest->detail, newChest->slot, 
                    newChest->value);
            sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newChest->detail, newChest->slot, 
                    newChest->value);
            writeFile(collect);
            printf("DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->chest->detail, equipped->chest->slot, 
                    equipped->chest->value);
            sprintf(discard, "DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->chest->detail, equipped->chest->slot, 
                    equipped->chest->value);
            writeFile(discard);
            #endif
            /*Equip the better item*/
            equipped->chest = newChest;
            equipped->chestVal = newChest->value;
        }
    }
}

/******************************************************************************
*Purpose: Compares current hand equipment with new hand equipment
*How it works: Swaps the current hand equipment if it is weaker than the new 
*              hand equipment, else if there is no hand equipment, wear it.
*How it relates: Called on through function pointer located inside gear struct
******************************************************************************/
void compareHands (Gear* newHands, Equip* equipped, int yloc, int xloc)
{
    #ifdef LOG
    char collect[2048];
    char discard[2048];
    #endif 
    /*If the slot is empty, just equip it*/
    if(equipped->hands == NULL)
    {
        /*Equip into empty slot*/
        equipped->hands = newHands;
        equipped->handsVal = newHands->value;
        #ifdef LOG
        printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->hands->detail, equipped->hands->slot, 
                equipped->hands->value);
        sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->hands->detail, equipped->hands->slot, 
                equipped->hands->value);
        writeFile(collect);
        #endif
    }
    else
    {
        if(equipped->hands->value < newHands->value)
        {
            #ifdef LOG
            printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newHands->detail, newHands->slot, 
                    newHands->value);
            sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newHands->detail, newHands->slot, 
                    newHands->value);
            writeFile(collect);
            printf("DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->hands->detail, equipped->hands->slot, 
                    equipped->hands->value);
            sprintf(discard, "DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->hands->detail, equipped->hands->slot, 
                    equipped->hands->value);
            writeFile(discard);
            #endif
            /*Equip the better item*/
            equipped->hands = newHands;
            equipped->handsVal = newHands->value;
        }
    }
}

/******************************************************************************
*Purpose: Compares current leg equipment with new leg equipment
*How it works: Swaps the current leg equipment if it is weaker than the new 
*              leg equipment, else if there is no leg equipment, wear it.
*How it relates: Called on through function pointer located inside gear struct
******************************************************************************/
void compareLegs (Gear* newLegs, Equip* equipped, int yloc, int xloc)
{
    #ifdef LOG
    char collect[2048];
    char discard[2048];
    #endif 
    /*If the slot is empty, just equip it*/
    if(equipped->legs == NULL)
    {
        /*Equip into empty slot*/
        equipped->legs = newLegs;
        equipped->legsVal = newLegs->value;
        #ifdef LOG
        printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->legs->detail, equipped->legs->slot, 
                equipped->legs->value);
        sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                xloc, yloc, equipped->legs->detail, equipped->legs->slot, 
                equipped->legs->value);
        writeFile(collect);
        #endif
    }
    else
    {
        if(equipped->legs->value < newLegs->value)
        {
            #ifdef LOG
            printf("COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newLegs->detail, newLegs->slot, 
                    newLegs->value);
            sprintf(collect, "COLLECT<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, newLegs->detail, newLegs->slot, 
                    newLegs->value);
            writeFile(collect);
            printf("DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->legs->detail, equipped->legs->slot, 
                    equipped->legs->value);
            sprintf(discard, "DISCARD<ITEM:GEAR, XLOC:%d, YLOC:%d, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    xloc, yloc, equipped->legs->detail, equipped->legs->slot, 
                    equipped->legs->value);
            writeFile(discard);
            #endif
            /*Equip the better item*/
            equipped->legs = newLegs;
            equipped->legsVal = newLegs->value;
        }
    }
}
