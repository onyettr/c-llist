/**  
 * @brief Test harness for single linked list swap operation
 * @file test_swap.cpp
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

int test_swap ( void )
{
  list_t *SwapTest  = NULL;
  list_t *SwapTest1 = NULL;
  list_t *SwapTest2 = NULL;
  list_t *SwapTest3 = NULL;
  
  // Sign on
  printf ("**** Linked List Test - swap\n");

  /*
   * test1 - lists are not created
   */
  printf("\tTest01 - swap list not created list ErrorCode -10 = %d\n", list_swap(SwapTest,SwapTest1));
  
  /*
   * test2 - sizes are not the same
   */
  SwapTest = list_create_fill(3, 100);
  SwapTest1= list_create_fill(5, 200);
  printf("\tTest02 - swap list not equal   list ErrorCode -15 = %d\n", list_swap(SwapTest,SwapTest1));

  /*
   * test3 - swap Positive
   */
  SwapTest2 = list_create_fill(3, 100);
  SwapTest3 = list_create_fill(3, 200);
  printf("\tTest03 - Lists before swap\n");
  list_show(SwapTest2);
  list_show(SwapTest3);  
  printf("\tTest03 - swap list correctly   list ErrorCode   0 = %d\n", list_swap(SwapTest2,SwapTest3));

  printf("\tTest03 - Lists after swap\n");
  list_show(SwapTest2);
  list_show(SwapTest3);  
  
  printf ("**** Linked List Test - swap  Ends\n");
  
  return 0;
}

//
// Fin
//
  
