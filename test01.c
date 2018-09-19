/**
 *****************************************************************************
 * 
 * MODULE: C Programming Examples
 *
 * @brief  Test harness
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
#include "list.h"
#include "test.h"

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
#define DIM(X) (int)(sizeof((X))/sizeof(int))

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

static int test01 ( void ) {
  list_t *p = NULL;

  printf("\ntest01 - create list\n" );

  p = list_create();

  printf("[%p] List created\n", (void*)p);
  list_show(p);

  list_delete(p);

  return 0;
}

static int test02 ( void ) {
  list_t *p = NULL;

  printf("\ntest02 - create list and add\n" );

  p = list_create();
  printf("[%p] list created\n", (void*)p);

  list_add ( p, 101);
  list_add ( p, 201);
  list_add ( p, 301);
  list_add ( p, 401);
  list_add ( p, 501);
  list_add ( p, 601);
  list_add ( p, 701);
  list_add ( p, 801);
  list_add ( p, 901);    
  
  list_show(p);
  list_delete(p);

  return 0;
}

static int test03 ( void ) {
  list_t *p = NULL;

  printf("\ntest03 - test list_add_front\n" );

  p = list_create();
  printf("test03 - test list_add-front as first element\n");
  list_add_front (p, 666);
  list_show(p);

  printf("test03 - test list_add-front element\n");  
  list_add ( p, 101);
  list_add ( p, 201);
  list_add ( p, 301);
  list_add ( p, 401);
  list_show(p);
  list_add_front (p, 999);
  list_show(p);
  list_add_front (p, 888);
  list_show(p);
  list_add_front (p, 777);
  list_show(p);
  
  return 0;
}

static int test04 ( void ) {
  list_t *p = NULL;
  node_t *n = NULL;
  int values[] = { 101, 201, 301, 401 };
  int dim = DIM(values);
  int i;
  
  printf("\ntest04 - search list, should fail\n" );

  n = list_search_value(p, 201);

  printf("\ntest04 - search list\n" );  
  p = list_create();

  for (i=0; i < dim; i++) {
    list_add ( p, values[i]);    
  }    
  list_show(p);

  for (i=0; i < dim; i++) {
    n = list_search_value(p, values[i]);
    if ( n != NULL ) {
      printf("Found value %d at %p\n", values[i], (void*)n);
    }
  }
  return 0;
}

int test_run ( void ) {
  int error_code = 0;

  error_code = test01();    /* Run one of the tests */
  error_code = test02();    /* Run one of the tests */
  error_code = test03();    /* Run one of the tests */ 
  error_code = test04();    /* Run one of the tests */
  
  return error_code;
}

/*
 Fin
*/
  
