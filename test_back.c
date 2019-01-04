/**
 * @brief  Test harness for single linked list_back operations
 * @file   test_back.c
 * @author onyettr
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

int test_back (void)
{
  list_t *addTest;
  list_t *addTest2;
  
  // Sign on
  printf("**** Linked List Test - push back\n");

  /*
   * create a new list
   */ 
  addTest = list_create();
  addTest2= list_create();
  
  /*
   * Add an element
   */
  printf("\tTest01 - return Tail, no list elements\n");
  printf("\tReturn (-1) = %d\n",list_get_back(addTest));

  printf("\tTest02 - return Tail, list has one elenment\n");
  list_add_element(addTest,201);
  printf("\tReturn (201) = %d\n", list_get_back(addTest));

  printf("\tTest03 - return back, list has two elements\n");
  list_add_element(addTest,301);
  printf("\tReturn (301) = %d\n", list_get_back(addTest));

  printf("\tTest04 - return back, list has new back element\n"); 
  list_push_back(addTest,111);
  printf("\tReturn (111) = %d\n", list_get_back(addTest));  

  list_show(addTest);

  printf("\tTest05 - push back, list has is empty\n"); 
  list_push_back(addTest2,111);
  printf("\tReturn (111) = %d\n", list_get_back(addTest2));  

  list_show(addTest2);
  
  printf("**** Linked List Class Test - back Ends\n");
  
  return 0;
}

