/**
 * @brief  C Programming Examples - Simple stack using single linked list
 * @author ronyett
 */
#include <stdio.h>
#include "list.h"

list_t *StackInit(void) {
  list_t *pNewList = NULL;

  pNewList = list_create();
  if ( pNewList == NULL ) {
    printf("StackInit - Failed to allocate list\n");
  }

  return pNewList;
}

int push(list_t *p, int value) {
  int ErrorCode;

  ErrorCode = list_add_element(p, value);

  return ErrorCode;
}

int pop (list_t *p) {
  int value;
  value = list_get_front(p);
  list_delete_front(p);

  return value;
}

bool empty(list_t *p) {
  return (list_size(p) == 0) ? true : false;
}

void display(list_t *p) {
  list_show(p);
}

int main ( void ){
  list_t *pStack;
  
  printf("Stack Using Linked list library\n");

  pStack = StackInit();
  push(pStack, 101);
  display(pStack);
  
  printf("Pop stack = %d\n", pop(pStack));
  display(pStack);
  printf("Pop stack = %d\n", pop(pStack));

  push(pStack, 101);
  push(pStack, 201);
  push(pStack, 301);
  push(pStack, 401);
  push(pStack, 501);
  while (!empty(pStack)) {
    printf("Pop stack = %d\n", pop(pStack));    
  }
}
