/**  
 * @brief Test harness for single linked list remove operation
 * @file test_remove.cpp
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

int test_remove ( void )
{
  list_t *rmTest  = NULL;
  list_t *rmTest3 = NULL;
  list_t *rmTest4 = NULL;
  list_t *rmTest5 = NULL;
  list_t *rmTest6 = NULL;      
  
  // Sign on
  printf ("**** Linked List Test - remove\n");

  /*
   * create a new list
   */ 
  rmTest = list_create();
  
  printf("\tTest01 - remove element from empty list ErrorCode -10 = %d\n", list_remove(rmTest,48));

  /*
   * Test2: remove positive single delete
   */
  printf("\tTest02 - remove one element\n");
  list_add_element(rmTest,101);
  list_add_element(rmTest,201);
  list_add_element(rmTest,301);  
  printf("\tNumber in list before removal = %d\n",list_size(rmTest));
  list_show(rmTest);
  list_remove(rmTest,201);    
  printf("\tNumber in list after  removal = %d\n",list_size(rmTest));
  list_show(rmTest);

  /*
   * Test3: remove positive mutiple delete
   */
  rmTest3 = list_create();  
  printf("\tTest03 - remove two elements\n");
  list_add_element(rmTest3,1001);
  list_add_element(rmTest3,2001);
  list_add_element(rmTest3,201);
  list_add_element(rmTest3,201);
  list_add_element(rmTest3,3001);
  list_add_element(rmTest3,4001);
  list_add_element(rmTest3,5001);
  list_add_element(rmTest3,6001);
  list_add_element(rmTest3,7001);  
  
  printf("\tNumber in list before removal = %d\n", list_size(rmTest3));
  list_show(rmTest3);
  list_remove(rmTest3,201);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest3));
  list_show(rmTest3);

  /*
   * Test4: remove positive mutiple delete
   */
  rmTest4 = list_create();  
  printf("\tTest04 - remove at start elements\n");
  list_add_element(rmTest4,201);  
  list_add_element(rmTest4,1001);
  list_add_element(rmTest4,3001);

  printf("\tNumber in list before removal = %d\n", list_size(rmTest4));
  list_show(rmTest4);
  list_remove(rmTest4,201);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest4));
  list_show(rmTest4);

  /*
   * Test5: remove positive at end
   */
  rmTest5= list_create();  
  printf("\tTest05 - remove at end elements\n");
  list_add_element(rmTest5,1001);
  list_add_element(rmTest5,3001);
  list_add_element(rmTest5,201);  

  printf("\tNumber in list before removal = %d\n", list_size(rmTest5));
  list_show(rmTest5);
  list_remove(rmTest5,201);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest5));
  list_show(rmTest5);

  /*
   * Test6: remove positive numerous elements
   */
  rmTest6= list_create();  
  printf("\tTest06 - remove numerous elements\n");
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,1001);
  list_add_element(rmTest6,2001);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,3001);
  printf("\tNumber in list before removal = %d\n", list_size(rmTest6));
  list_show(rmTest6);
  list_remove(rmTest6,201);      
  printf("\tNumber in list after  removal = %d\n", list_size(rmTest6));
  list_show(rmTest6);
  
  printf("**** Linked List Class Test Template - remove  Ends\n");
  
  return 0;
}

//
// Fin
//
  
