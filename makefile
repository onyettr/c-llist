#*******************************************************************************
# File name        : makefile
# File description : C Single Linked list implementation
# Author           : ronyett
#*******************************************************************************

SRC_DIR		= 	.
OBJECT_DIR	= 	$(SRC_DIR)/object
MAKE_DIR_CMD	= 	mkdir $(OBJECT_DIR)

#
# 1) If you want gcov coverage enable the PLFAGS option and rebuild all
# 2)
#
CC  		= 	gcc
LINK  		= 	gcc
AR		= 	ar
CHK   		= 	checkmk
CHECK_FOR_CHK	:= 	$(shell command -v $(CHK) 2> /dev/null)

#*******************************************************************************
# Build options
#*******************************************************************************

# gcov and gprof build options
COVPFLAGS	= 	-fprofile-arcs -ftest-coverage
PROFLAGS	= 	-pg
#PFLAGS		= 	$(COVFLAGS)

DEBUG 		=	-g
CFLAGS		=	-c -std=c99 -Wall -pedantic $(PFLAGS)
#CFLAGS		+=	-DDEEP_TRACE
LFLAGS		=	$(PFLAGS) -static -L.

#
# Code checking with splint
#
CODE_CHECK       = 	splint
CODE_CHECK_ARGS	 = 	-showfunc -mustfreefresh -nullpass -nullret -noeffect

#
# Libs, objs targets
# liblist library is built from trap handling and the list implementation. 
#
OBJS  		     = $(OBJECT_DIR)/main.o 		\
		       $(OBJECT_DIR)/test_create.o	\
		       $(OBJECT_DIR)/test_search.o	\
		       $(OBJECT_DIR)/test_empty.o       \
		       $(OBJECT_DIR)/test_front.o      	\
		       $(OBJECT_DIR)/test_back.o      	\
		       $(OBJECT_DIR)/test_size.o       	\
		       $(OBJECT_DIR)/test_add.o       	\
		       $(OBJECT_DIR)/test_del.o       	\
		       $(OBJECT_DIR)/trap.o		\
		       $(OBJECT_DIR)/poortool.o 

STACK_OBJ	     = $(OBJECT_DIR)/stack.o

TEST_HDRS	     = test.h

LIBS  		     = liblist.a
TEST_STACK 	     = list_test.ts

#*******************************************************************************
# Build targets:
# all		Creates object directory, builds executable and runs checker
# stack.exe     Stack example using linked list library
# lib		Build only the list library, no test harness
# splint-it	run the Syntax checker
# clean		Delete object and library files
#*******************************************************************************

all:	$(OBJECT_DIR) list.exe liblist.a test_harness stack.exe

# The old order of linking chestnut had me going here! Objs need to be first in the list with library last
list.exe:	$(OBJS) $(LIBS)
	$(LINK) $(OBJS) $(LFLAGS) -llist -o list.exe

# Example of a stack using a linked list
stack.exe:	$(STACK_OBJ) liblist.a
	$(LINK) $(STACK_OBJ) $(LFLAGS) -llist -o stack.exe

liblist.a:	$(OBJECT_DIR)/list.o
	$(AR) rcs liblist.a $(OBJECT_DIR)/list.o

# Main objects
$(OBJECT_DIR):
	-$(MAKE_DIR_CMD)

$(OBJECT_DIR)/main.o:		main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o $(OBJECT_DIR)/main.o

$(OBJECT_DIR)/list.o:	list.c
	$(CC) $(CFLAGS) $(DEBUG) list.c -o $(OBJECT_DIR)/list.o

$(OBJECT_DIR)/trap.o:		trap.c
	$(CC) $(CFLAGS) $(DEBUG) trap.c -o $(OBJECT_DIR)/trap.o

$(OBJECT_DIR)/test_create.o:	test_create.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_create.c -o $(OBJECT_DIR)/test_create.o

$(OBJECT_DIR)/test_search.o:	test_search.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_search.c -o $(OBJECT_DIR)/test_search.o

$(OBJECT_DIR)/test_empty.o:	test_empty.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_empty.c -o $(OBJECT_DIR)/test_empty.o

$(OBJECT_DIR)/test_front.o:	test_front.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_front.c -o $(OBJECT_DIR)/test_front.o

$(OBJECT_DIR)/test_back.o:	test_back.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_back.c -o $(OBJECT_DIR)/test_back.o

$(OBJECT_DIR)/test_size.o:	test_size.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_size.c -o $(OBJECT_DIR)/test_size.o

$(OBJECT_DIR)/test_add.o:	test_add.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_add.c -o $(OBJECT_DIR)/test_add.o

$(OBJECT_DIR)/test_del.o:	test_del.c $(TEST_HDRS)
	$(CC) $(CFLAGS) $(DEBUG) test_del.c -o $(OBJECT_DIR)/test_del.o

$(OBJECT_DIR)/poortool.o:	poortool.c
	$(CC) $(CFLAGS) $(DEBUG) poortool.c -o $(OBJECT_DIR)/poortool.o

$(OBJECT_DIR)/stack.o:		stack.c
	$(CC) $(CFLAGS) $(DEBUG) stack.c -o $(OBJECT_DIR)/stack.o

#
# This is the "check" target: Test harness is in stack_check.ts file and 
# this is converted by "check" into a C file which is linked to give another
# executable. 
# 
# NOTE: This will not build if you have the Profiling enabled as the libstack.a 
# contains gcov 
#
test_harness: liblist.a list_check.ts
ifndef CHECK_FOR_CHK
	@echo "** checkmk command not found"
else
	$(CHK) list_check.ts > list_check.c
	$(CC) -o list_check.exe list_check.c -static -L. -lcheck -llist
endif

#
# Code checking target
#
splint-it:
	$(CODE_CHECK) $(CODE_CHECK_ARGS) list.c     
	$(CODE_CHECK) $(CODE_CHECK_ARGS) main.c  
	$(CODE_CHECK) $(CODE_CHECK_ARGS) trap.c   
	$(CODE_CHECK) $(CODE_CHECK_ARGS) test_create.c

clean:
	rm -f list.exe
	rm -f stack.exe
	rm -f list_check.exe
	rm -f liblist.a
	rm -f $(OBJECT_DIR)/main.o
	rm -f $(OBJECT_DIR)/trap.o
	rm -f $(OBJECT_DIR)/list.o
	rm -f $(OBJECT_DIR)/poortool.o
	rm -f $(OBJECT_DIR)/test_create.o
	rm -f $(OBJECT_DIR)/test_search.o
	rm -f $(OBJECT_DIR)/test_empty.o
	rm -f $(OBJECT_DIR)/test_front.o
	rm -f $(OBJECT_DIR)/test_size.o
	rm -f $(OBJECT_DIR)/test_back.o
	rm -f $(OBJECT_DIR)/test_add.o
	rm -f $(OBJECT_DIR)/test_del.o
	rm -f $(OBJECT_DIR)/stack.o
	rm -f *.gcno
	rm -f *.gcda
	rm -f core

#
# Fin
#

