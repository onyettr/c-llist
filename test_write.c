/**
 * @brief Test harness for single linked list write operations
 * @file test_write.c
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
******************************************************************************
Private Constants
******************************************************************************
*/

/*
******************************************************************************
Private Types
******************************************************************************
*/

/*
******************************************************************************
Private variables (static)
******************************************************************************
*/

/*
******************************************************************************
Private Macros
******************************************************************************
*/

/*
******************************************************************************
Global variables
******************************************************************************
*/

/*
******************************************************************************
Exported Global variables
******************************************************************************
*/

/*
******************************************************************************
Prototypes of all functions contained in this file (in order of occurance)
******************************************************************************
*/

int test_write ( void )
{
  list_t *writeTest;
  
  // Sign on
  printf("**** Linked List Test - write\n");

  /*
   * create a new list
   */ 
  writeTest = list_create();

  printf("\tTest01a - write single element, empty list\n");
  printf("Result %d = ERROR_LIST_EMPTY\n", list_write_position(writeTest, 3, 101));
  
  printf("\tTest01b - write single element, bad position\n");
  list_add_element(writeTest,10);
  list_show(writeTest);
  printf("Result %d = ERROR_LIST_BAD_POSITON\n", list_write_position(writeTest, 3, 101));

  printf("\tTest02a  - write single element, good positon\n");
  list_add_element(writeTest,20);
  list_show(writeTest);  	 
  printf("Result %d = SUCCESS\n", list_write_position(writeTest, 1, 101));
  list_show(writeTest);  	 	 

  printf("\tTest02b  - write single element, good position,longer list\n");
  list_add_element(writeTest,201);
  list_add_element(writeTest,202);
  list_add_element(writeTest,203);  
  list_show(writeTest);  	 
  printf("Result %d = SUCCESS\n", list_write_position(writeTest, 3, 1001));
  list_show(writeTest);  	 	 
  
  printf("**** Linked List Test - add Ends\n");
  
  return 0;
}

