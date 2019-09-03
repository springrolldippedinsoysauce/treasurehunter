#Author: Ong Ming Hang    
#Date modified: 25/05/2019 
CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror
OBJ = TreasureHunter.o FileIO.o LinkedList.o MovementProcessor.o ItemProcessor.o CompareGear.o LogWriter.o
EXEC = TreasureHunter

#Add LOG to the CFLAGS and recompile the program
ifdef LOG
CFLAGS += -D LOG
LOG : clean $(EXEC) 
endif

#Add AI to the CLAGS and recompile the program
ifdef AI
CFLAGS += -D AI
LOG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

TreasureHunter.o : TreasureHunter.c all_header.h
	$(CC) -c TreasureHunter.c $(CFLAGS)

FileIO.o : FileIO.c all_header.h
	$(CC) -c FileIO.c $(CFLAGS)

MovementProcessor.o : MovementProcessor.c all_header.h
	$(CC) -c MovementProcessor.c $(CFLAGS)

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)

ItemProcessor.o : ItemProcessor.c all_header.h
	$(CC) -c ItemProcessor.c $(CFLAGS)

CompareGear.o : CompareGear.c all_header.h
	$(CC) -c CompareGear.c $(CFLAGS)

LogWriter.o : LogWriter.c all_header.h
	$(CC) -c LogWriter.c $(CFLAGS)

clean :
	rm -rf $(EXEC) $(OBJ)
