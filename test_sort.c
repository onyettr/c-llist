/**
 * @brief Test harness for single linked list sort operations
 * @file test_sort.c
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

int test_sort ( void )
{
  list_t *sortTest;
  int ErrCode = SUCCESS;
  
  // Sign on
  printf("**** Linked List Test - sort\n");

  /*
   * create a new list
   */ 
  sortTest = list_create();
  
  /*
   * Test01:Sort empty list
   */
  ErrCode = list_sort(sortTest);
  printf("\tTest01  - size of list 0 = %d, Res = %s\n", list_size(sortTest), list_error_to_string(ErrCode));
  if (ErrCode != ERROR_LIST_EMPTY) {
    exit(-1);
  }
  
  /*
   * Test02:Sort one element
   */
  list_add_element(sortTest, 60000);    

  printf("\tTest20a - size of list 2 = %d\n", list_size(sortTest));
  list_sort(sortTest);
  list_show(sortTest);

  /*
   * Test02:Sort many elements
   */
  list_add_element(sortTest, 120);
  list_add_element(sortTest, 111);
  list_add_element(sortTest, 11);  
  list_add_element(sortTest, 12);
  list_add_element(sortTest, 6);  

  list_show(sortTest);  
  printf("\tTest20b - size of list 6 = %d\n", list_size(sortTest));
  list_sort(sortTest);
  list_show(sortTest);
  
  printf("**** Linked List Test - sort Ends\n");
  
  return 0;
}

