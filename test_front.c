/**
 * @brief  Test harness for single linked list add to front operations
 * @file   test_front.c
 * @author onyettr
 *
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
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

int test_front (void)
{
  list_t *addTest;  

  // Sign on
  printf("Linked List Class Test - front\n");

  /*
   * create a new list
   */ 
  addTest = list_create();
  
  /*
   * Add an element
   */
  printf("\tTest01 - return front, no list elements\n");
  printf("\tReturn (-1) = %d\n", list_get_front(addTest));

  printf("\tTest02 - return front, list has one element\n");

  list_add_element(addTest,200);
  printf("\tReturn (200) = %d\n", list_get_front(addTest));

  printf("\tTest03 - return front, list has two elements, front still same\n");
  list_add_element(addTest,300);
  printf("\tReturn (200) = %d\n", list_get_front(addTest));

  printf("\tTest04 - return front, list has new front element\n");
  list_add_front(addTest,111);
  printf("\tReturn (111) = %d\n", list_get_front(addTest));

  list_show(addTest);
  
  return 0;
}

  
