/**
 *****************************************************************************
 * @file   main.c
 * @brief  test harness calling
 * @author ronyett
 ***************************************************************************** 
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "poortool.h"

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
extern void poortool_init();

/*
 * Adds a node onto the head of list at the front.
 */

/*
******************************************************************************
Prototypes of all functions contained in this file (in order of occurance)
******************************************************************************
*/

int main ( void ) {
  
  (void)test_create();
  (void)test_empty();
  (void)test_size();
#if 0 
   poortool_init();
#endif
  
   return 0;
}