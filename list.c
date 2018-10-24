/**
 *****************************************************************************
 * @file   list.c
 * @brief  C Singly Linked list implementation
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

/**
 * @fn      static int isEmpty(stack_t *pStack) - test if list isEmpty
 *
 * @brief   check if list is Empty
 * @param   *p  - the list
 * @return  Returns "true" or "false"
 */
static bool isEmpty(list_t *p) {
   return p->pHead == NULL ? true : false;
}

/**
 *  @fn     static node_t *NewNode(int value) 
 *
 *  @brief  Create an internal new node
 *
 *  @param  int value 
 *
 *  @return node_t * 
 * 
 *  @note   This is used only by list_add operation and so is private to this file. 
 */
static node_t *NewNode(int value) {
   node_t *p = NULL;

   p = (node_t *)malloc(sizeof(node_t));
   if ( p != NULL ) {
      p->value = value;
      p->pNext = NULL;
      p->pPrev = NULL;
      p->pData = NULL;
   }

   return (node_t *)p;
}

/**
 *  @fn     list_t *list_create(void)
 *
 *  @brief  Create a new list
 *
 *  @return NULL is failure
 *  @note   create a list
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

/**
 * @fn        void list_add_element ( list_t *p, int value ) 
 *
 * @brief     This adds a node to the end of the list
 *
 * @param[in] *p         Pointer to the list to add to 
 * @param[in] value      Value of element
 *
 */
int list_add_element ( list_t *p, int value ) {
   node_t *pNode = NULL; 

   /*
    * Create a new node, store the value 
    */
   pNode = NewNode(value);
   if ( pNode == NULL ) {
      printf("list_add: failed to create a new node\n");

      return -1;
   }
  
   if (p->pHead == NULL ) {
       /*
        * Add this new node to the list as this is the first entry
        */
       p->pHead = pNode;
       p->pTail = pNode;
       pNode->pNext = NULL;
#if defined (DEEP_TRACE)       
       printf("list_add: (first) node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);
#endif       
   } else {
       /*
        * We are not the first, so add to the list at the end
        */
       p->pTail->pNext = pNode;  
       p->pTail = pNode;
#if defined (DEEP_TRACE)       
       printf("list_add: node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);
#endif       
   }

   p->NodeCount += 1;

   return 0;
}

/**
 *
 * @fn        void list_add_front ( list_t *p, int value ) 
 *
 * @brief     Adds a node to the front of the list
 * 
 * @param[in] *p   - Pointer to the list
 * @param[in] int  - Value to add
 *
 * @return    none
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

#if defined (DEEP_TRACE)      
      printf("list_add_front: (first) node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);
#endif      
   } else {
      pHold = p->pHead;      /* Save off the head of the list                   */
      p->pHead = pNode;      /* Move the head of the list to this new element   */
      pNode->pNext = pHold;  /* Point new element back to initial first element */
   }

   p->NodeCount += 1;
}

/**
 *
 * @fn        void list_add_back ( list_t *p, int value ) 
 *
 * @brief     Adds a node to the back of the list
 * 
 * @param[in] *p   - Pointer to the list
 * @param[in] int  - Value to add
 *
 * @return    none
 */
void list_add_back ( list_t *p, int value ) {
   node_t *pNode = NULL; 
   node_t *pHold = NULL;

   (void)pNode;
   (void)pHold;
}

/**
 * @fn        
 *
 * @brief     
 * 
 * @param[in] *p   - Pointer to the list
 * @param[in] int  - Value to add
 *
 * @return    
 */
int  list_get_position(list_t *p, int position) {
  return 0;
}

/**
 * @fn        
 *
 * @brief     
 * 
 * @param[in] *p   - Pointer to the list
 *
 * @return    Value at Front
 */
int  list_get_front   (list_t *p) {
   return 0;  
}

/**
 * @fn        
 *
 * @brief     
 * 
 * @param[in] *p   - Pointer to the list
 * @param[in] int  - Value to add
 *
 * @return    
 */
int  list_get_back    (list_t *p) {
  return 0;
}

/**
 * @fn        int  list_size (list_t *p) 
 *
 * @brief     Returns the size or number of nodes in a list
 * 
 * @param[in] *p   - Pointer to the list
 *
 * @return    Size of the list
 */
int  list_size (list_t *p) {
   int ListSize = 0;

   if (list_empty(p)) {
     return ListSize;
   }

   ListSize = p->NodeCount;

   return ListSize;
}

/**
 * @fn        bool list_empty       (list_t *p)
 *
 * @brief     Test is the list is empty
 * 
 * @param[in] *p   - Pointer to the list
 *
 * @return    TRUE if empty, FALSE if not
 * @note      Also tests if the list has been created. 
 */
bool list_empty (list_t *p) {
#if defined (DEBUG_TRACE)
   printf("TRACE: list_empty called\n");
#endif
     
   if (isEmpty(p) && (p != NULL)) {
      return true;
   }

   return false;
}

/**
 * @fn        list_t *GetListHead   (list_t *p) 
 *
 * @brief     Return the head of the list
 * 
 * @param[in] *p   - Pointer to the list
 *
 * @return    Pointer to the Head or Null if empty
 */
node_t *GetListHead   (list_t *p) {
   if (list_empty(p)) {
     return (node_t *)NULL;
   }

   return p->pHead;
}

/**
 * @fn        list_t *GetListTail   (list_t *p)
 *
 * @brief     Return the Tail of the List
 * 
 * @param[in] *p   - Pointer to the list
 *
 * @return    Pointer to the Tail or NULL if empty
 */
node_t *GetListTail   (list_t *p) {
   if (list_empty(p)) {
     return (node_t *)NULL;
   }

   return p->pTail;
}

/**
 * @fn        int list_delete ( list_t *p ) - delete a complete list
 * @brief     delete a given list plus any associated nodes. 
 *
 * @param[in] *p    Pointer to the list to delete
 *
 * @return    int 0 for succcess, -1 if fail
 *
 * @note      This will scan the whole list of nodes and delete the nodes 
 *            before deleting the list_p itself. 
 */
int list_delete ( list_t *p ) {
    node_t *pNode = NULL;  
    node_t *pNext = NULL;

    if ( p == NULL ) {
       printf("list_delete: list is empty\n");
       return -1;
    }

    pNode = p->pHead;        /* Point at first node  */
    while ( pNode ) {
       pNext = pNode->pNext;  /* Pick up the next one */

#if defined (DEEP_TRACE)    
       printf("[%p] Next->[%p], Value %5d\n",
	      (void *)pNode,
	      (void *)pNode->pNext,
	      pNode->value);
#endif
    
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

    return 0;
}  

/**
 * @fn    node_t *list_search_value(list_t *p, int value) {
 * @brief Seach list for a given value
 * @param[in] *p
 * @param[in] int
 * @return     node_t *
 * @note   search for a value and return associated node
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

#if defined(DEEP_TRACE)      
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

/**
 * @fn     void list_show ( list_t *p )
 * @brief  Display items in the list
 * @param  *p - pointer to list
 * @return none
 */
void list_show ( list_t *p ) {
  node_t *n = NULL;
  

  printf("   Address   \tValue\t   pNext\tNumber of Nodes = %d\n", p->NodeCount);
  n = p->pHead;
  while ( n ) {
     printf("[%p]\t%5d\t[%p]\n",
  	     (void *)n,
	     n->value,
	    (void *)n->pNext);

     n = n->pNext;
  }
}

