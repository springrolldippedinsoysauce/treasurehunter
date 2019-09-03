/****************************
*Author: Ong Ming Hang      *
*Date modified: 25/05/2019  *
****************************/
#ifndef TREASURE_H                                                                  
#define TREASURE_H                                                                  
/******************************************************************************
*Purpose: Forward declaration of typedef struct Gear
*How it works: Allows Gear to be defined as an uninitialised struct
*How it relates: -
******************************************************************************/
typedef struct Gear Gear;
/******************************************************************************
*Purpose: Forward declaration of typedef struct Equip
*How it works: Allows Equip to be defined as an uninitialised struct
*How it relates: -
******************************************************************************/
typedef struct Equip Equip;

/******************************************************************************
*Purpose: Function pointer to compare gears
*How it works: When dereferenced, it is a function which compare slots 
*              depending of what function it is pointing at
*How it relates: Stored inside Treasure struct so when the player encounters
*                a gear, immediately calls it.
******************************************************************************/
typedef void (*Compare)(Gear*,Equip*,int,int);

/******************************************************************************
*Purpose: Equip struct that holds all of the current items that the player has
*How it works: Declares a list of variables to store items as player walks
*              through it
*How it relates: Used in movementProcessor and it is only malloc'd once, each
*                Gear pointer is set to NULL at first, when a gear is collected
*                , the Gear will point to the new gear.
******************************************************************************/
struct Equip
{
    Gear* head; 
    Gear* chest; 
    Gear* hands; 
    Gear* legs;
    int headVal;
    int chestVal;
    int handsVal;
    int legsVal;
    int totalMagic;
    int totalCoin; 
};
                                                                                   
/******************************************************************************
*Purpose: Contains the information of gear item
*How it works: -
*How it relates: Used in itemProcessor function to store any gear as a Gear
*                struct 
******************************************************************************/
struct Gear                                                                 
{                                                                       
    char type;        
    char detail[512];                                                               
    char slot[512];                                                                 
    int value;                                                                     
    Compare comparePtr;
};
                                                                             
/******************************************************************************
*Purpose: Contains the information of magic item
*How it works: -
*How it relates: Used in itemProcessor function to store any magic as a Magic
*                struct
******************************************************************************/
typedef struct                                                                  
{                                                                               
    char type;        
    char detail[512];                                                               
    int value;                                                                     
}Magic;                                                                            
                                                                                   
/******************************************************************************
*Purpose: Contains the information of coin item
*How it works: -
*How it relates: Used in itemProcessor function to store any coin as a Coin
*                struct
******************************************************************************/
typedef struct                                                                     
{
    char type;        
    int value;           
}Coin;    
                                                                         
/******************************************************************************
*Purpose: Contains the information of every valid item type
*How it works: -
*How it relates: Used in itemProcessor function to create a 2D array of 
*                Treasure struct
******************************************************************************/
typedef struct                                                                  
{
    char type;
    Gear* gear;
    Magic* magic;   
    Coin* coin;                                                     
}Treasure;           
#endif 
