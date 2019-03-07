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
 *  @param  value - element to add
 *  @return node_t * - new node
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
 * @fn        list_t *GetListHead   (list_t *p)
 * @brief     Return the head of the list
 * @param[in] *p   - Pointer to the list
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
 * @brief     Return the Tail of the List
 * @param[in] *p   - Pointer to the list
 * @return    Pointer to the Tail or NULL if empty
 */
node_t *GetListTail   (list_t *p) {
   if (list_empty(p)) {
     return (node_t *)NULL;
   }

   return p->pTail;
}

/**
 *  @fn     list_t *list_create(void)
 *  @brief  Create a new list
 *  @return NULL is failure
 *  @note   create a list to whihc "elements" nodes are added. 
 */
list_t *list_create(void) { /*@null@*/
  list_t *p = (list_t*)NULL;
#if defined(DEBUG_TRACE)
   printf("list_create: called\n");
#endif   
   p = (list_t *)malloc(sizeof(list_t)); /* @null */
   if ( p != NULL) {
      p->pFront = (node_t *)NULL;
      p->pTail  = (node_t *)NULL;
      p->pHead  = (node_t *)NULL;
      p->NodeCount = 0;
   }
#if defined (DEEP_TRACE)
   printf("list_create: %p \n", (void*)p);
#endif   

   return p; 
}

/**
 *  @fn     list_t *list_create_fixed(int n)
 *  @brief  Create a new list of n Elements
 *  @return NULL is failure
 *  @note   create a list of n (Elements) nodes are added. 
 */
list_t *list_create_fixed(int n) { /*@null@*/
  list_t *p = (list_t*)NULL;
  int i;
#if defined(DEBUG_TRACE)
   printf("list_create_fixed: called, elements = %d\n", n);
#endif   

   p = list_create();
   if ( p != NULL ) {
      for (i=0; i < n; i++) {
	list_add_element(p, 0);
      }
   }

   return p; 
}

/**
 *  @fn        list_t *list_create_fill(int n, int value)
 *  @brief     Create a new list of n Elements and fill with value
 *  @param[in] n  - number of elements to create
 *  @param[in] value - fill pattern
 *  @return    NULL is failure otherwise list_t pointer
 *  @note      create a list of n (Elements) nodes are added and fill with value
 */
list_t *list_create_fill(int n, int value) {
  list_t *p = (list_t*)NULL;
  int i;
#if defined(DEBUG_TRACE)
  printf("list_create_fill: called, elements = %d, fill %d\n", n, value);
#endif   

   p = list_create();
   if ( p != NULL ) {
      for (i=0; i < n; i++) {
	list_add_element(p, value);
      }
   }

   return p; 
}

/**
 *  @fn     int list_assign(list_t *p, int n, int value)
 *  @brief  assign (fill) n elements to value
 *  @param[in] p - Pointer to the list
 *  @param[in] n - number to fill
 *  @param[in] value - fill pattern
 *  @return SUCCESS or List empty, too small, too big
 *  @note   
 */
int list_assign(list_t *p, int n, int value) {
  node_t *pNode = (node_t*)NULL;
  int i;
#if defined(DEBUG_TRACE)
   printf("list_assign: called, elements = %d\n", n);
#endif   

   if (list_empty(p)) {
     return ERROR_LIST_EMPTY;
   }

   if (n > list_size(p)) {
     return ERROR_LIST_TOO_SMALL;
   }

   pNode = GetListHead(p);
   for (i=0; i < n; i++) {
     pNode->value = value;
     pNode = pNode->pNext;
   }

   return SUCCESS;
}

/**
 * @fn        void list_add_element ( list_t *p, int value ) 
 * @brief     This adds a node to the end of the list 
 * @param[in] p          Pointer to the list to add to 
 * @param[in] value      Value (fill) of element
 * @return    SUCCESS is ok, ERROR_LIST_ALLOCATION_FAILED
 */
int list_add_element ( list_t *p, int value ) {
   node_t *pNode = NULL; 

   /*
    * Create a new node, store the value 
    */
   pNode = NewNode(value);
   if ( pNode == NULL ) {
      printf("list_add: failed to create a new node\n");

      return ERROR_LIST_ALLOCATION_FAILED;
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

   return SUCCESS;
}

/**
 * @fn        int list_push_front ( list_t *p, int value ) 
 * @brief     Adds a node to the front of the list
 * @param[in] *p    - Pointer to the list
 * @param[in] value -  to add
 * @return    0 (SUCCESS
 */
int list_push_front ( list_t *p, int value ) {
   node_t *pNode = NULL; 
   node_t *pHold = NULL;
  
   /*
    * Create a new node, store the value 
    */
   pNode = NewNode(value);
   if ( pNode == NULL ) {
      printf("list_push_front: failed to create a new node\n");

     return ERROR_LIST_ALLOCATION_FAILED;
   }

   if (p->pHead == NULL ) {
      /*
       * Add this new node to the list as this is the first entry
       */
      p->pHead = pNode;
      p->pTail = pNode;
      pNode->pNext = NULL;

#if defined (DEEP_TRACE)      
      printf("list_push_front: (first) node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);
#endif      
   } else {
      pHold = p->pHead;      /* Save off the head of the list                   */
      p->pHead = pNode;      /* Move the head of the list to this new element   */
      pNode->pNext = pHold;  /* Point new element back to initial first element */
   }

   p->NodeCount += 1;

   return SUCCESS;
}

/**
 * @fn        int list_push_back ( list_t *p, int value ) 
 * @brief     Adds a node to the back of the list
 * @param[in] *p    - Pointer to the list
 * @param[in] value - to add
 * @return    none
 */
int list_push_back ( list_t *p, int value ) {
   node_t *pTemp = NULL; 
   node_t *pCurrentTail;
   
   /* 
    * Create new "back" element
    */
   pTemp = NewNode(value);
   pCurrentTail = GetListTail(p);  /* Get the current Tail element                   */

   if(pCurrentTail == NULL) {
     /*
      * We are now back (and front!)
      */
     p->pTail = pTemp;
     p->pHead = pTemp;
   } else {
     pCurrentTail->pNext = pTemp;    /* Current Tail points to the new element created */
     p->pTail = pTemp;               /* Advances the Tail to the new Tail elemenet     */
   }

   p->NodeCount++;                 /* Increase the number of nodes                   */

   return SUCCESS;
}

/**
 * @fn        void list_add_position( list_t *p, int position, int value)
 * @brief     Adds a node to a list at 'Position'
 * @param[in] *p       - Pointer to the list
 * @param[in] position - place to add
 * @param[in] value    - to add
 * @return    none
 */
int list_add_position( list_t *p, int position, int value ) {
   node_t *pTemp = NULL; 
   node_t *pCurrent;
   node_t *pPrevious;   
   int i;
#if defined(DEEP_TRACE)
   printf("list_add_position: %p %d = %d\n", (void *)p, position, value);
#endif
   
   if ( position > list_size(p)) {
     printf("list_add_position: position is beyond end of the list\n");

     return ERROR_LIST_BAD_POSITION;
   }

   if (position == 0) {
     list_push_front(p,value);

     return SUCCESS;
   }

   /* 
    * Create new "back" element
    */
   pTemp = NewNode(value);
   pTemp->pNext = NULL;

   pCurrent = GetListHead(p);  /* Start of the list */
   
   /*
    * Traverse the list until we get to position
    */
   for (i=1; i < position; i++) {
      pPrevious = pCurrent;
      pCurrent = pCurrent->pNext;
   }

   /* Now we are at Position, lets insert the new node */
   pPrevious->pNext = pTemp;
   pTemp->pNext     = pCurrent;
#if defined (DEEP_TRACE)
   printf("list_add_position: [%p]\n", pCurrent);
#endif   
   p->NodeCount++;                 /* Increase the number of nodes                   */

   return SUCCESS;
}

/**
 * @fn        void list_write_position( list_t *p, int position, int value)
 * @brief     Adds a node to a list at 'Position'
 * @param[in] *p       - Pointer to the list
 * @param[in] position - place to add
 * @param[in] value    - to add
 * @return    none
 * @note      Does not create a new node, assumes list is already created. List Size remains the same
 */
int  list_write_position(list_t *p, int position, int value) {
   node_t *pTemp = NULL; 
   node_t *pCurrent;
   node_t *pPrevious;   
   int i;
#if defined(DEEP_TRACE)
   printf("list_write_position: %p %d = %d\n", (void *)p, position, value);
#endif
   if (list_empty(p)) {
     printf("list_get_position - list is empty");

     return ERROR_LIST_EMPTY;
   }
   
   if ( position > list_size(p)) {
     printf("list_write_position: position is beyond end of the list\n");

     return ERROR_LIST_BAD_POSITION;
   }

   pCurrent = GetListHead(p);  /* Start of the list */
   
   /*
    * Traverse the list until we get to position
    */
   for (i=0; i < position; i++) {
      pPrevious = pCurrent;
      pCurrent = pCurrent->pNext;
   }

   /* Now we are at Position, lets insert the new node */
   pPrevious->value = value;
#if defined (DEEP_TRACE)
   printf("list_write_position: [%p] = %d\n", pPrevious,value);
#endif   

   return SUCCESS;
}

/**
 * @fn        int  list_get_position(list_t *p, int position) 
 * @brief     Return an element value given a position in the list
 * @param[in] *p   - Pointer to the list
 * @param[in] position of element in the list
 * @return    int  - Value at the list position or -1 if empty
 */
int  list_get_position(list_t *p, int position) {
  node_t *pCurrent;
  int value = 0;
  int i;

#if defined(DEEP_TRACE)
  printf("list_get_position: %p %d\n", (void*)p,position);
#endif
  
  if (list_empty(p)) {
     printf("list_get_position - list is empty");

     return ERROR_LIST_EMPTY;
  }

  if (position >= list_size(p)) {
     printf("list_get_position: ERROR_LIST_BAD_POSITION\n");    

     return ERROR_LIST_BAD_POSITION;
  }
  
  /*
   * Traverse the list until we get to position
   */
  pCurrent = GetListHead(p);  /* Start of the list */
  for (i=0; i < position; i++) {  
     pCurrent = pCurrent->pNext;
  }

  value = pCurrent->value;

#if defined(DEEP_TRACE)  
  printf("list_get_position: [%p] %d returns %d\n", (void*)pCurrent, position, value);
#endif  

  return value;
}

/**
 * @fn        int  list_get_front   (list_t *p)
 * @brief     Return the value at the front of the list
 * @param[in] *p   - Pointer to the list
 * @return    Value at Front or -1 if empty
 */
int  list_get_front   (list_t *p) {
  int value = SUCCESS;
#if (DEBUG_TRACE)
  printf("TRACE: list_get_front called\n");
#endif  

  if (!list_empty(p)) {
    value = (p->pHead)->value;        
  } else {
    return ERROR_LIST_EMPTY;
  }
  
  return value;  
}

/**
 * @fn        int  list_get_back    (list_t *p)
 * @brief     return the value at the back of the list
 * @param[in] *p   - Pointer to the list
 * @return    value
 */
int  list_get_back    (list_t *p) {
  int value = 0;
#if (DEBUG_TRACE)
  printf("TRACE: list_get_back called\n");
#endif  

  if (!list_empty(p)) {
    value = (p->pTail)->value;        
  } else {
    return ERROR_LIST_EMPTY;
  }
  
  return value;  
}

/**
 * @fn        int  list_size (list_t *p) 
 * @brief     Returns the size or number of nodes in a list
 * @param[in] *p   - Pointer to the list
 * @return    Size of the list
 */
int  list_size (list_t *p) {
   int ListSize = 0;  
#if defined (DEBUG_TRACE)
   printf("TRACE: list_size called\n");
#endif

   if (list_empty(p)) {
     return ListSize;
   }

   ListSize = p->NodeCount;

   return ListSize;
}

/**
 * @fn        bool list_empty       (list_t *p)
 * @brief     Test is the list is empty
 * @param[in] *p   - Pointer to the list
 * @return    TRUE if empty, FALSE if not
 * @note      Also tests if the list has been created. 
 */
bool list_empty (list_t *p) {
#if defined (DEBUG_TRACE)
   printf("TRACE: list_empty called\n");
#endif

   if (p == NULL) {
      return true;
   }
   if (isEmpty(p)) {
      return true;
   }

   return false;
}

/**
 * @fn        int list_delete_element(list_t *p, int position) 
 * @brief     delete a given element at 'position'
 * @param[in] *p    Pointer to the list to delete
 * @param[in] position in the list
 * @return    none
 * @note      
 */
int list_delete_element(list_t *p, int position) {
  node_t *pCurrent;
  node_t *pPrevious;

#if defined(DEEP_TRACE)
  printf("list_delete_element: position = %d\n", position);
#endif
 
  if (list_size(p) == 0) {
    return ERROR_LIST_EMPTY;
  }
  
  if (position > list_size(p)) {
    printf("list_delete_element - position beyond list_size\n");

    return ERROR_LIST_BAD_POSITION;
  }

  /*
   * test if position is first
   */
  pCurrent = GetListHead(p);
  if (position == 0) {
    p->pHead = pCurrent->pNext;
    pCurrent->pNext = NULL;
  } else {
     int i;
     for (i=0; i < position; i++) {
         pPrevious = pCurrent;
         pCurrent = pCurrent->pNext;
	 //	 printf("list_delete_element: %d Curr %p, next %p\n",i,(void*)pPrevious, (void*)pCurrent);	 
      }
      pPrevious->pNext = pCurrent->pNext;    /* Previous entry is now pointing to one beyond the deleted entry */      
  }

#if defined(DEEP_TRACE)
  printf("list_delete_element: deleting %p\n", (void *)pCurrent);
#endif
  
  free(pCurrent);                            /* Delete the node                                                */
  p->NodeCount--;                            /* Decrement the node count                                       */

  return SUCCESS;
}

/**
 * @fn        int list_delete_front(list_t *p)
 * @brief     delete the Front element 
 * @param[in] *p    Pointer to the list to delete the element
 * @note      
 */
int list_delete_front(list_t *p) {
   int ErrCode; 

   ErrCode = list_delete_element(p,0);

   return ErrCode;
}
 
/**
 * @fn        int list_delete_back(list_t *p) 
 * @brief     delete the Back element
 * @param[in] *p    Pointer to the list to delete
 * @return    SUCCESS or ERROR_LOST_EMPTY
 * @note      
 */
int list_delete_back(list_t *p) {
  node_t *pCurrent;
  
  /*
   * if the list is empty, lets return
   */
  if (list_size(p) <= 0) {
    return ERROR_LIST_EMPTY;
  }

  /*
   * if we have only one element, then last is first!
   */
  if(list_size(p) == 1) {
    free(p->pHead);          /* Free the last node      */
    p->pHead = (node_t *)NULL; /* Plug the root         */
    p->pTail = (node_t *)NULL; /* Plug the root         */
    p->NodeCount = 0;        /* No nodes anymore        */

    return SUCCESS;
  }

  /*
   * Scan from the Head of the list until we find the end
   * NOTE: we are looking beyond the next for the end
   */
  pCurrent = p->pHead;

  while( pCurrent->pNext->pNext != NULL ) {
    pCurrent = pCurrent->pNext;
  }

  /* pCurrent is now at the last (but one) element node */
  free(pCurrent->pNext);     /* Delete the last element */

  pCurrent->pNext = NULL;    /* Current is now the last */
  p->pTail = pCurrent;       /* Update the Tail to last */
  p->NodeCount--;            /* Decrement the nodeCount */
  
  return SUCCESS;
}

/**
 * @fn        int list_clear ( list_t *p ) - delete a complete list
 * @brief     delete a given list plus any associated nodes. 
 * @param[in] *p    Pointer to the list to delete
 * @return    int 0 for succcess, -1 if fail
 * @note      This will scan the whole list of nodes and delete the nodes 
 *            before deleting the list_p itself. 
 */
int list_clear ( list_t *p ) {
    node_t *pNode = NULL;  
    node_t *pNext = NULL;

    if ( p == NULL || list_size(p) == 0 ) {
       return ERROR_LIST_EMPTY;
    }

    pNode = p->pHead;         /* Point at first node  */
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
 * @fn    int list_search(list_t *p, int value) {
 * @brief Seach list for a given value
 * @param[in] *p    - pointer to the list
 * @param[in] value - search element
 * @return    int   - Position in the list
 * @note  search for a value and return associated position, -1 means not found
 */
int list_search(list_t *p, int value) {
  int Position = 0;
  node_t *np;
  
  if ( p == NULL) {
    printf("list_search_value: no list to search!\n");

    return -1;
  }

  np = p->pHead;        /* get first node */
  while ( np ) {
    if ( np->value == value ) {

#if defined(DEEP_TRACE)      
      printf("list_search_value: found!\n");
#endif

      return Position;
    }
    np = np->pNext;
    Position++;
  }

  return -1;         /* Not found */
}

/**
 * @fn        void list_reverse ( list_t *p )
 * @brief     Reverse the contents of the list passed
 * @param[in] *p - list to reverse
 * @return    ERROR_LIST_EMPTY, SUCCESS
 */
int list_reverse ( list_t *p ) {
  node_t *pCurrent = NULL;
  node_t *pNext    = NULL;
  node_t *pPrevious= NULL;

  if (list_size(p) == 0) {
    printf("list_reverse: Empty!\n");

    /* Thrower(e_empty); */
    
    return ERROR_LIST_EMPTY;
  }

  /*
   *     List_t                  node_t               node_t
   *    pHead    ------------>   value                value
   *    pTail    ------------>(1)pNext -->(3)Previous pNext ---> NULL
   *                               ^                   ^ (2)
   *                              pCurrent             pNext
   *                                                   pNext (5)
   * 1) pTail = pHead
   * 2) pNext = pCurrent->pNext
   * 3) pCurrent->pNext - pPrevious
   * 4) pPrevious = pCurrent
   * 5) pCurrent = pNext    This swaps
   */
  pCurrent = GetListHead(p);              /* Point to start of the list         */
  // printf("pCurrent (Listhead) %p, Tail %p\n",(void *)pCurrent, (void*)p->pTail);
  p->pTail = p->pHead;                    /* Swap the tail to point to the head */
  // printf("pTail %p, pHead %p\n", (void*)p->pTail, (void*)p->pHead);

  while ( pCurrent != NULL ) {
    pNext = pCurrent->pNext;
//  printf("pNext %p\n", (void*)pNext);
    pCurrent->pNext = pPrevious;
//  printf("pCurrent->Next  %p\n", (void*)pCurrent->pNext);
    pPrevious = pCurrent;
//  printf("pCurrent->next %p\n",(void*)pCurrent->pNext);
    pCurrent = pNext;
//  printf("pCurrent %p\n",(void*)pCurrent);
  }

  p->pHead = pPrevious;
//  printf("pHead %p\n",(void*)p->pHead);

  return SUCCESS;
}

/**
 * @fn        int list_remove(list_t *p, int value) 
 * @brief     remove elements containing duplicate value
 * @param[in] p     - the list
 * @param[in] value - to remove
 * @return    none
 * @note
 */
int list_remove (list_t *p, int value) {
    int position = 0;
    node_t *pCurrent;

#if defined(DEEP_TRACE)
    printf("list_remove: Value %d\n", value);
#endif
    
    /*
     * List is empty?
     */
    if (list_size(p) == 0) {
       return ERROR_LIST_EMPTY;
    }

    /*
     * Scan the list for duplicates, if one is found, reset to the start and search again
     */
    pCurrent = GetListHead(p);
    while (pCurrent) {
      if ( list_get_position(p,position) == value ) {
	list_delete_element(p,position);
        pCurrent = GetListHead(p);
	position = 0;
      } else {
	pCurrent = pCurrent->pNext;
	position++;
      }
    }

    return SUCCESS;
}

/**
 * @fn        int list_remove_if(list_t *p, bool (*predFun)(int value))) 
 * @brief     remove elements based on predFunc == true
 * @param[in] p     - the list
 * @param[in] (*predFunc)
 * @return    none
 * @note
 */
int list_remove_if (list_t *p, bool (*predFunc)(int value)) {
    int position = 0;
    node_t *pCurrent;

#if defined(DEEP_TRACE)
    printf("list_remove_if: \n");
#endif
    
    /*
     * List is empty?
     */
    if (list_size(p) == 0) {
       return ERROR_LIST_EMPTY;
    }

    if (predFunc == NULL) {
      return ERROR_LIST_EMPTY;
    }

    /*
     * Scan the list for duplicates, if one is found, reset to the start and search again
     */
    pCurrent = GetListHead(p);
    while (pCurrent) {
      int item;

      item = list_get_position(p,position);
      if ( predFunc(item) ) {
	list_delete_element(p,position);
        pCurrent = GetListHead(p);
	position = 0;
      } else {
	pCurrent = pCurrent->pNext;
	position++;
      }
    }

    return SUCCESS;
}

/**
 * @fn        int list_swap(list_t *p, list_t *p1)
 * @brief     Swap p1 for p
 * @param[in] p     - the first list
 * @param[in] p1    - the second list
 * @return    SUCCESS if ok, ERROR_LIST_SIZE_MISMATCH if list sizes are not equal
 * @note
 */
int list_swap(list_t *p, list_t *p1) {
   node_t *pCurrentListOne;
   node_t *pCurrentListTwo;   
#if defined(DEEP_TRACE)
   printf("list_swap: %p %p\n", (void *)p, (void *)p1);
#endif
    
    /*
     * Lists are empty?
     */
    if (list_size(p) == 0 ||
	list_size(p1)== 0) {
       return ERROR_LIST_EMPTY;
    }

    if (list_size(p) != list_size(p1)) {
       return ERROR_LIST_SIZE_MISMATCH;
    }

    pCurrentListOne = GetListHead(p);
    pCurrentListTwo = GetListHead(p1);
    while (pCurrentListOne) {
      int tmp;

      tmp = pCurrentListOne->value;
      pCurrentListOne->value = pCurrentListTwo->value;
      pCurrentListTwo->value = tmp;

      pCurrentListOne = pCurrentListOne->pNext;
      pCurrentListTwo = pCurrentListTwo->pNext;      
    }
    
    return SUCCESS;  
}

/**
 * @fn        int  list_sort        (list_t *p)
 * @brief     Sort list p
 * @param[in] p     - list
 * @return    SUCCESS if ok, ERROR_LIST_SIZE_MISMATCH if list sizes are not equal
 * @note
 */
int  list_sort        (list_t *p) {
  int minimum;
  int temp;  
  int temp1;
  int temp2;
  int i;
  int n;

  printf("list_sort size %d\n", list_size(p));
  n = list_size(p);
  
  for (i=0; i < n; i++) {
    int j;
    minimum = i;
    for (j=(i+1); j < n; j++) {
      temp1 = list_get_position(p, minimum);
      temp2 = list_get_position(p, j);
      printf("i %d j %d temp1 %d temp2 %d\n", i, j, temp1, temp2);
      if (temp1 > temp2) {
	minimum = j;
      }
    }
    temp = list_get_position(p, minimum);
    temp1= list_get_position(p, i);

    list_add_position(p,minimum,temp1);
    list_add_position(p,i,temp);
    printf("SWAP i %d minimum %d temp1 %d temp2 %d\n", i, minimum, temp, temp1);    
  }
  
  return SUCCESS;  
}

/**
 * @fn     void list_show ( list_t *p )
 * @brief  Display items in the list
 * @param  *p - pointer to list
 * @return none
 */
void list_show ( list_t *p ) {
  node_t *pCurrent = NULL;
  int NumberOfNodes = 0;
  
  if (!list_empty(p)) {
    int Count = 0;

    printf("      Address   \tValue\t   pNext\t#Nodes [%d] pHead [%p] pTail [%p]\n",
	   p->NodeCount,
	   (void *)p->pHead,
	   (void *)p->pTail);

    NumberOfNodes = list_size(p);
    
    pCurrent = GetListHead(p);
    while ((pCurrent) && (NumberOfNodes > 0)) {
       printf("%2d [%p]\t%5d\t[%p]",
	      Count,
	      (void *)pCurrent,
	      pCurrent->value,
	      (void *)pCurrent->pNext);

       if (p->NodeCount == 1) {
	 printf("    <--- HEAD   <--- TAIL\n");	 
       } else if (pCurrent == GetListHead(p)) {
	 printf("    <--- HEAD\n");
       } else if (pCurrent == GetListTail(p)) {
	 printf("\t         <--- TAIL\n");	 
       } else {
	 printf("\n");
       }
       
       pCurrent = pCurrent->pNext;
       Count++;
       NumberOfNodes--;
    }
  } else {
    printf("\t#Nodes [%d] pHead [%p] pTail [%p]\n",
	   p->NodeCount,
	   (void *)p->pHead,
	   (void *)p->pTail);
  }
}

