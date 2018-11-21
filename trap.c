/**
 *****************************************************************************
 * MODULE: C Programming Examples
 *
 * @author: onyettr 
 *
 * PURPOSE: Simple Stack implementation
 ***************************************************************************** 
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include "trap.h"

/**
 * @fn    void Thrower(exception_t exp)  
 * @brief exception handing
 * @param exp - exception type
 */
void Thrower(exception_t exp) {
  printf( "ouch something bad went on = ");
  if (exp == e_overflow ) {
    printf ("OverFlowExcep");
  } else if (exp == e_underflow) {
    printf ("UnderFlowExcep");
  } else if (exp == e_outofmemory) {
    printf ("OutofMemoryExcep()");
  } else if (exp == e_empty) {
    printf("empty()");
  }
  
  printf("\n");
}

