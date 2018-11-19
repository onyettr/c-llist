/**
 * @brief Test harness for single linked list search operations
 * @file test_search.c
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

int test_search ( void )
{
  // Sign on
  printf("**** Linked List Test - search\n");

  /*
   * create a new list
   */ 
  list_t *SearchTest;

  SearchTest = list_create();  
  printf("\tTest01 - search on empty list %s \n",list_search(SearchTest, 100) == -1 ? "PASSED" : "FAIL");

  list_add_element(SearchTest,100);
  printf("\tTest02 - search on list %d element = %d (0 )\n",list_size(SearchTest), list_search(SearchTest,100));

  list_add_element(SearchTest,200);
  list_add_element(SearchTest,300);
  printf("\tTest03 - search on list %d element = %d (2 )\n",list_size(SearchTest), list_search(SearchTest,300));

  list_add_element(SearchTest,400);
  list_add_element(SearchTest,500);
  printf("\tTest04 - search on list %d element = %d (-1)\n",list_size(SearchTest), list_search(SearchTest,700));  
  
  printf("**** Linked ListTest - search Ends\n");

  return 0;
}

