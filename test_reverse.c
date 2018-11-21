/**
 * @brief Test harness for single linked list reverse
 * @file test_rev.c
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

int test_reverse ( void )
{
  list_t *revTest1;
  list_t *revTest2;
  list_t *revTest3;
  
  // Sign on
  printf("**** Linked List Test - list reverse\n");

  /*
   * Test01 - single element
   */
  printf("\tTest01 - rev single element\n");
  revTest1 = list_create();
  list_add_element(revTest1, 1);
  printf("\tNumber in list before reverse = %d\n", list_size(revTest1));  
  list_show(revTest1);  
  list_reverse(revTest1);  
  list_show(revTest1);

  /*
   * Test02 - mulitple elements
   */
  printf("\tTest02 - rev multiple element\n");
  revTest2 = list_create();
  list_add_element(revTest2, 1);
  list_add_element(revTest2, 2);
  list_add_element(revTest2, 3);
  list_add_element(revTest2, 4);
  list_add_element(revTest2, 5);      
  printf("\tNumber in list before reverse = %d\n", list_size(revTest2));
  list_show(revTest2);
  list_reverse(revTest2);
  list_show(revTest2);  

  /*
   * Test03 - no elements
   */
  printf("\tTest03 - rev zero element, exception to be thrown\n");
  revTest3 = list_create();
  list_reverse(revTest3);

  printf("**** Linked List Test - reverse Ends\n");
  
  return 0;
}

//
// Fin
//
  
