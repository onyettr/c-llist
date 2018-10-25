/**
 * @brief Test harness for single linked list add operations
 * @file test_add.cpp
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

int test_add ( void )
{
  list_t *addTest;
  list_t *emplaceTest;
  
  // Sign on
  printf("**** Linked List Test - add\n");

  /*
   * create a new list
   */ 
  addTest = list_create();  
  printf("\tTest01a - add single element\n");
  list_add_element(addTest,10);
  list_show(addTest);  

  printf("\tTest01b - add more   elements\n");
  list_add_element(addTest,20);
  list_add_element(addTest,30);
  list_add_element(addTest,40);
  list_add_element(addTest,50);
  list_add_element(addTest,60);  
  list_show(addTest);
  printf("\tTest01b - size of list %d\n", list_size(addTest));

  printf("\tTest02a - add to front\n");  
  list_add_front(addTest, 111);
  list_show(addTest);
  printf("\tTest02a - size of list %d\n", list_size(addTest));

  printf("\tTest03a - add to back\n");;  
  list_add_back(addTest, 222);
  list_show(addTest);
  printf("\tTest03a - size of list %d\n", list_size(addTest));

  emplaceTest = list_create();
  
  printf("\tTest04a - emplace\n");
  list_add_element(emplaceTest, 1);
  list_add_element(emplaceTest, 2);
  list_add_element(emplaceTest, 3);
  list_add_element(emplaceTest, 4);  
  list_show(emplaceTest);
  printf("\tTest04a - size of list 4 = %d\n", list_size(emplaceTest));

  printf("\tTest05a - emplace at position 2\n");    
  list_add_position(emplaceTest, 2, 5);
  list_show(emplaceTest);  
  printf("\tTest05a - size of list %d\n", list_size(emplaceTest));

  printf("\tTest05b get at position 2 (5) %d\n", list_get_position(emplaceTest, 2));
  
  printf("\tTest05c - emplace at position 0\n");    
  list_add_position(emplaceTest, 0, 555);
  list_show(emplaceTest);  
  printf("\tTest05c - size of list %d\n", list_size(emplaceTest));
  printf("\tTest05c get at position 2 (555) %d\n", list_get_position(emplaceTest, 0));

  printf("\tTest05d - emplace at position size+1\n");    
  list_add_position(emplaceTest, (list_size(emplaceTest)+1), 100);
  
  printf("**** Linked List Test - add Ends\n");
  
  return 0;
}

