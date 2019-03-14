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

int test_front (void)
{
  list_t *addTest;  
  int ErrCode = SUCCESS;
  
  // Sign on
  printf("Linked List Test - front\n");

  /*
   * create a new list
   */ 
  addTest = list_create();
  
  /*
   * Add an element
   */
  printf("\tTest01 - return front, no list elements\n");
  ErrCode = list_get_front(addTest);
  printf("\tReturn (%s) = %d\n", list_error_to_string(ErrCode),ErrCode);
  if ( ErrCode != ERROR_LIST_EMPTY) {
    exit(-1);
  }
    
  printf("\tTest02 - return front, list has one element\n");
  list_add_element(addTest,200);
  ErrCode = list_get_front(addTest);
  printf("\tReturn (200) = %d\n", ErrCode);
  if (ErrCode != 200) {
    exit(-1);
  }

  printf("\tTest03 - return front, list has two elements, front still same\n");
  list_add_element(addTest,300);
  ErrCode = list_get_front(addTest);
  printf("\tReturn (200) = %d\n", ErrCode);
  if (ErrCode != 200) {
    exit(-1);
  }

  printf("\tTest04 - return front, list has new front element\n");
  list_push_front(addTest,111);

  ErrCode = list_get_front(addTest);
  printf("\tReturn (111) = %d\n", ErrCode);
  if (ErrCode != 111) {
    exit(-1);
  }

  list_show(addTest);

  printf("Linked List Test - front - ENDS\n");
  
  return 0;
}

  
