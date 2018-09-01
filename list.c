/*
 *****************************************************************************
 * MODULE: C Programming
 *
 * $Header: $
 * $Archive:$
 * 
 * $Workfile: $
 *
 * $Author: Onyettr $
 *
 * NAME: Richard Onyett 
 * EMAIL: 
 *
 * PURPOSE: Linked list implementation
 * 
 * $Revision:$
 * $History: $
 *
 ***************************************************************************** 
 */

/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "trap.h"

/*
******************************************************************************
Prototypes of all functions contained in this file (in order of occurance)
******************************************************************************
*/
static bool isEmpty(list_t *pq);
static node_t *NewNode(int value);

/*
 -- --------------------------------------------------------------
 -- static int isEmpty(stack_t *pStack) - test if list isEmpty
 -- 
 -- Returns "true" or "false"
 -- --------------------------------------------------------------
*/
static bool isEmpty(list_t *p) {
  return p->pHead == NULL ? true : false;
}

/*
 -- --------------------------------------------------------------
 -- list_t *list_create(void) - create a new list type.
 --
 -- Return NULL is failure
 -- --------------------------------------------------------------
*/
list_t *list_create(void) { /*@null@*/
  list_t *p = (list_t*)NULL;
  
  p = (list_t *)malloc(sizeof(list_t)); /* @null */
  if ( p != NULL) {
    p->pFront = (node_t *)NULL;
    p->pTail  = (node_t *)NULL;
    p->pHead  = (node_t *)NULL;
    p->NodeCount = 0;
  }

  return p; 
}

/*
 -- --------------------------------------------------------------
 -- \fn static node_t *NewNode(int value) - Create an internal
 --     new node
 --
 -- This is used only by list_add operation and so is private to 
 -- this file. 
 -- --------------------------------------------------------------
*/
static node_t *NewNode(int value) {
  node_t *p = NULL;

  p = (node_t *)malloc(sizeof(node_t));
  if ( p != NULL ) {
    p->value = value;
    p->pNext = NULL;
    p->pPrev = NULL;

    return p;
  }

  return p;
}

/*!
 -- --------------------------------------------------------------
 -- \fn    void list_add ( list_t *p, int value ) 
 -- \brief This adds a node to the end of the list
 -- \param list_p *p         Pointer to the list
 -- --------------------------------------------------------------
*/
void list_add ( list_t *p, int value ) {
  node_t *pNode = NULL; 

  /*
   * Create a new node, store the value 
   */
  pNode = NewNode(value);
  if ( pNode == NULL ) {
    printf("list_add: failed to create a new node\n");

    return;
  }
  
  if (p->pHead == NULL ) {
    /*
     * Add this new node to the list as this is the first entry
     */
    p->pHead = pNode;
    p->pTail = pNode;
    pNode->pNext = NULL;
    printf("list_add: (first) node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);
  } else {
    /*
     * We are not the first, so add to the list
     */
    p->pTail->pNext = pNode;  
    p->pTail = pNode;
    printf("list_add: node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);    
  }

  p->NodeCount += 1;
}

/*!
 -- --------------------------------------------------------------
 -- \fn  void list_add_front ( list_t *p, int value ) 
 -- \brief This adds a node to the front of the list
 -- \param list_p *p         Pointer to the list
 -- --------------------------------------------------------------
*/
void list_add_front ( list_t *p, int value ) {
  node_t *pNode = NULL; 
  node_t *pHold = NULL;
  
  /*
   * Create a new node, store the value 
   */
  pNode = NewNode(value);
  if ( pNode == NULL ) {
    printf("list_add_front: failed to create a new node\n");

    return;
  }

  if (p->pHead == NULL ) {
    /*
     * Add this new node to the list as this is the first entry
     */
    p->pHead = pNode;
    p->pTail = pNode;
    pNode->pNext = NULL;
    printf("list_add_front: (first) node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);
  } else {
    pHold = p->pHead;      /* Save off the head of the list                   */
    p->pHead = pNode;      /* Move the head of the list to this new element   */
    pNode->pNext = pHold;  /* Point new element back to initial first element */
  }

  p->NodeCount += 1;
}

/*!
 -- --------------------------------------------------------------
 -- \fn void list_delete ( list_t *p ) - delete a complete list
 -- 
 -- list_t *p    Pointer to the created list.
 -- 
 -- This will scan the whole list of nodes and delete the nodes 
 -- before deleting the list_p itself. 
 -- --------------------------------------------------------------

*/
void list_delete ( list_t *p ) {
  node_t *pNode = NULL;  
  node_t *pNext = NULL;

  if ( p == NULL ) {
    printf("list_delete: list is empty\n");

    return;
  }

  pNode = p->pHead;        /* Point at first node  */
  while ( pNode ) {
    pNext = pNode->pNext;  /* Pick up the next one */

    printf("[%p] Next->[%p], Value %5d\n",
	   (void *)pNode,
	   (void *)pNode->pNext,
	   pNode->value);

    free(pNode);           /* Delete current node  */
    pNode = pNext;         /* Move down the list   */
  }

  /*
   * Delete list head itself. Setting values back to beginning as 
   * was found this memory was still valid even after the free() 
   * call
   */
  p->pFront = NULL;
  p->pTail  = NULL;
  p->pHead  = NULL;
  p->NodeCount = 0;
  free(p);
}  

/*
 -- --------------------------------------------------------------
 -- \fn    node_t *list_search_value(list_t *p, int value) {
 -- \brief Seach list for a given value
 -- \param list_t *p
 -- \param int value
 -- --------------------------------------------------------------
*/
node_t *list_search_value(list_t *p, int value) {
  node_t *np = NULL;

  if ( p == NULL) {
    printf("list_search_value: no list to search!\n");

    return np;
  }

  np = p->pHead;        /* get first node */
  while ( np ) {
    if ( np->value == value ) {
#if defined(DEBUG)      
      printf("list_search_value: found!\n");
#endif
      return np;
    }
    np = np->pNext;
  }

  return np;  
}

/*
 -- --------------------------------------------------------------
 -- \fn    void list_reverse ( list_t *p )
 -- \brief Reverse the contents of the list passed
 -- \param list_t *p
 -- --------------------------------------------------------------
*/
void list_reverse ( list_t *p ) {
}

/*
 -- --------------------------------------------------------------
 -- \fn    void list_show ( list_t *p )
 -- \brief Display items in the list
 -- \param list_t *p
 -- --------------------------------------------------------------
*/
void list_show ( list_t *p ) {
  node_t *n = NULL;

  if (isEmpty(p)) {
    printf ("empty - nothing to display\n");

    return;
  }

  printf("************* List ***************\n");
  printf("Node count [%d]\n", p->NodeCount);

  n = p->pHead;
  while ( n ) {
    printf("[%p] Next->[%p], Value %5d\n",
	   (void *)n,
	   (void *)n->pNext,
	   n->value);
    n = n->pNext;
  }
}

