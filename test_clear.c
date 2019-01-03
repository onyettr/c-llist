/**
 * @brief Test harness for single linked list delete operations
 * @file test_del.c
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

int test_clear ( void )
{
  list_t *delTest;
  
  // Sign on
  printf("**** Linked List Test Template - clear\n");

  /*
   * create a new list
   */ 
  delTest = list_create();

  printf("\tTest01 - clear empty list,error -10 = %d\n", list_clear(delTest));    
  
  /*
   * Add an element
   */
  printf("\tTest02 - clear list\n");      
  list_add_element(delTest, 302);
  list_add_element(delTest, 403);
  list_add_element(delTest, 504);
  list_add_element(delTest, 605);  
  printf("\tNumber in list before clear (4) = %d\n",list_size(delTest));
  list_show(delTest);

  list_clear(delTest);
  printf("\tNumber in list after clear (0) = %d\n",list_size(delTest));

  printf("**** Linked List Test Template - clear Ends\n");
  
  return 0;
}
