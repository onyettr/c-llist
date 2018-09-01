# Simple makefile
#
# 1) If you want gcov coverage enable the PLFAGS option and rebuild all
# 2)
#
CC    =g++
AR    =ar
LINK  =g++
DEBUG =-g
#PFLAGS=-fprofile-arcs -ftest-coverage
CFLAGS=-c -Wall -pedantic $(PFLAGS)
LFLAGS=$(PFLAGS) -static -L.

# -DDEBUG_TRACE	Will turn on deep trace per function
# -DEXCEPTION	Will use the real exceptions with the 'try' that's in the test harness

# Code checking
CODE_CHECK=splint
CODE_CHECK_ARGS=-showfunc -hints -compdef -nullret +loopexec -mustfreeonly

OBJS  = main.o trap.o test01.o poortool.o
LIBS  = liblist.a

all:	list.exe liblist.a splint-it

# The old order of linking chestnut had me going here! Objs need to be first in the list with library last
list.exe:	$(OBJS) $(LIBS)
	$(LINK) $(OBJS) $(LFLAGS) -llist -o list.exe

liblist.a:	list.o
	$(AR) rcs liblist.a list.o

main.o:		main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o main.o
list.o:	list.c
	$(CC) $(CFLAGS) $(DEBUG) list.c -o list.o
trap.o:		trap.c
	$(CC) $(CFLAGS) $(DEBUG) trap.c -o trap.o
test01.o:	test01.c
	$(CC) $(CFLAGS) $(DEBUG) test01.c -o test01.o
poortool.o:	poortool.c
	$(CC) $(CFLAGS) $(DEBUG) poortool.c -o poortool.o

splint-it:
	$(CODE_CHECK) $(CODE_CHECK_ARGS) main.c  
	$(CODE_CHECK) $(CODE_CHECK_ARGS) trap.c   
	$(CODE_CHECK) $(CODE_CHECK_ARGS) test01.c
	$(CODE_CHECK) $(CODE_CHECK_ARGS) list.c     

clean:
	rm -f list.exe
	rm -f list.o
	rm -f liblist.a
	rm -f test01.o
	rm -f main.o
	rm -f trap.o
	rm -f poortool.o
	rm -f *.gcno
	rm -f *.gcda
	rm -f core

#
# Fin
#

