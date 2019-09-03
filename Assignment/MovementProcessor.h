/****************************
*Author: Ong Ming Hang      *
*Date modified: 25/05/2019  *
****************************/
#ifndef IP_H
#define IP_H
void movementProcessor(Treasure**, int, int, LinkedList*);
void itemCollector(Treasure**, int, int, Equip*);
void displayStats(Equip*, char*);
void equipFree(void*);
#endif
