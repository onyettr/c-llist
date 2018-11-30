/**
 * @brief Test harness for single linked list assign
 * @file test_assign.c
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

int test_assign ( void )
{
  list_t *assignTest;
  
  // Sign on
  printf("**** Linked List Test - list assign\n");

  /*
   * Test01 assign test on empty list, exception to be thrown
   */
  assignTest = list_create();
  printf("\tTest01 - assign test empty list, (-10) = %d\n", list_assign(assignTest,7,100));

  /*
   * Test02 assign test on list with more element, exception to be thrown
   */
  list_add_element(assignTest,200);
  printf("\tTest02 - assign test not enough element, (-13) = %d\n", list_assign(assignTest,7,100));	 
 
  /*
   * Test03 correct assignment
   */
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);  
  printf("\tNumber in list before assign = %d\n",list_size(assignTest));
  list_show(assignTest);

  list_assign(assignTest, 7, 100);
  list_show(assignTest);

  printf("**** Linked List Test - assign Ends\n");
  
  return 0;
}

//
// Fin
//
  
