/**
 *****************************************************************************
 * @file   trap.h
 * @brief  Header file for simple stack
 * @author ronyett
 ***************************************************************************** 
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#ifndef __TRAP_H__
#define __TRAP_H__

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

typedef enum exception {
  e_overflow    = 100,
  e_underflow   = 200,
  e_outofmemory = 300
} exception_t;

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
void Thrower(exception_t exp);

#endif // __TRAP_H__

