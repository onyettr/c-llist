/**  
 * @brief Test harness for single linked list remove_if operation
 * @file test_remove_if.cpp
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

bool is_odd (int value) {
  return (value%2) == 1;  
}

int test_remove_if ( void )
{
  list_t *rmTest  = NULL;
  list_t *rmTest3 = NULL;  
  list_t *rmTest4 = NULL;
  list_t *rmTest5 = NULL;
  list_t *rmTest6 = NULL;
  
  // Sign on
  printf ("**** Linked List Test - remove_if\n");

  /*
   * create a new list
   */ 
  rmTest = list_create();
  
  printf("\tTest01 - remove_if element from empty list ErrorCode -10 = %d\n", list_remove(rmTest,48));

  /*
   * Test2: remove_if positive single delete
   */
  printf("\tTest02 - remove_if one element is odd\n");
  list_add_element(rmTest,15);
  list_add_element(rmTest,20);
  list_add_element(rmTest,40);  
  printf("\tNumber in list before removal = %d\n",list_size(rmTest));
  list_show(rmTest);
  list_remove_if(rmTest,is_odd);    
  printf("\tNumber in list after  removal = %d\n",list_size(rmTest));
  list_show(rmTest);

  /*
   * Test3: remove positive mutiple delete
   */
  rmTest3 = list_create();  
  printf("\tTest03 - remove_if two elements odd\n");
  list_add_element(rmTest3,100);
  list_add_element(rmTest3,200);
  list_add_element(rmTest3,201);
  list_add_element(rmTest3,300);
  list_add_element(rmTest3,400);
  list_add_element(rmTest3,500);
  list_add_element(rmTest3,600);
  list_add_element(rmTest3,700);  
  
  printf("\tNumber in list before removal = %d\n", list_size(rmTest3));
  list_show(rmTest3);
  list_remove_if(rmTest3,is_odd);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest3));
  list_show(rmTest3);

  /*
   * Test4: remove positive mutiple delete
   */
  rmTest4 = list_create();  
  printf("\tTest04 - remove_if at start elements\n");
  list_add_element(rmTest4,201);  
  list_add_element(rmTest4,100);
  list_add_element(rmTest4,300);

  printf("\tNumber in list before removal = %d\n", list_size(rmTest4));
  list_show(rmTest4);
  list_remove_if(rmTest4,is_odd);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest4));
  list_show(rmTest4);

  /*
   * Test5: remove positive at end
   */
  rmTest5= list_create();  
  printf("\tTest05 - remove_if at end elements\n");
  list_add_element(rmTest5,100);
  list_add_element(rmTest5,300);
  list_add_element(rmTest5,201);  

  printf("\tNumber in list before removal = %d\n", list_size(rmTest5));
  list_show(rmTest5);
  list_remove_if(rmTest5,is_odd);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest5));
  list_show(rmTest5);

  /*
   * Test6: remove positive numerous elements
   */
  rmTest6= list_create();  
  printf("\tTest06 - remove_if numerous elements\n");
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,100);
  list_add_element(rmTest6,200);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,300);
  printf("\tNumber in list before removal = %d\n", list_size(rmTest6));
  list_show(rmTest6);
  list_remove_if(rmTest6,is_odd);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest6));
  list_show(rmTest6);

  printf("**** Linked List Test Template - remove_if  Ends\n");
  
  return 0;
}

//
// Fin
//
  
