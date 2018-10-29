/**
 * @brief Test harness for single linked list delete operations
 * @file test_del.c
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

static void test_delete_front(void) {
  list_t *delTest;

  /*
   * create a new list
   */ 
  delTest = list_create();  

  list_add_element(delTest, 101);
  list_add_element(delTest, 102);
  list_show(delTest);  
  list_delete_front(delTest);
  printf("\tTest01a - del front element\n");
  printf("\tReturn (102) = %d\n", list_get_front(delTest));
  list_show(delTest);  
}

static void test_delete_back(void) {
  list_t *delTest;
  list_t *delTest1b;
  list_t *delTest1c;  

  /*
   * create a new list
   */ 
  delTest = list_create();  

  printf("\tTest01a - del back element\n");  
  list_add_element(delTest, 101);
  list_add_element(delTest, 102);
  list_add_element(delTest, 103);  
  list_show(delTest);  
  list_delete_back(delTest);
  printf("\tReturn (102) = %d\n", list_get_back(delTest));
  list_show(delTest);

  printf("\tTest01b - del back element, zero elements\n");
  delTest1b = list_create();
  if (delTest1b == NULL) {
    printf("FAILED TO ALLOCATE!\n");
  } else
    printf("delTest1b %p, Nodes %d\n",(void *)delTest1b, delTest1b->NodeCount);
  //  printf("\tReturn (-10) = %d\n", list_delete_back(delTest1b));

  printf("\tTest01c - del back element, one element\n");
  delTest1c = list_create();
  list_add_element(delTest1c,200);
  printf("\tReturn (-10) = %d\n", list_delete_back(delTest1c));  
}

int test_delete ( void )
{
  // Sign on
  printf("**** Linked List Test - del\n");

  test_delete_front();
  test_delete_back ();
  
  printf("**** Linked List Test - del Ends\n");
  
  return 0;
}

