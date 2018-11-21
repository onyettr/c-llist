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
 *  @fn     list_t *list_create(void)
 *
 *  @brief  Create a new list
 *
 *  @return NULL is failure
 *
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
 * @fn        void list_add_element ( list_t *p, int value ) 
 *
 * @brief     This adds a node to the end of the list
 *
 * @param[in] *p         Pointer to the list to add to 
 * @param[in] value      Value of element
 *
 * @return    = if ok, -1 is we have a malloc fail. 
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
 *
 * @fn        int list_add_front ( list_t *p, int value ) 
 *
 * @brief     Adds a node to the front of the list
 * 
 * @param[in] *p    - Pointer to the list
 * @param[in] value -  to add
 *
 * @return    0 (SUCCESS)
 */
int list_add_front ( list_t *p, int value ) {
   node_t *pNode = NULL; 
   node_t *pHold = NULL;
  
   /*
    * Create a new node, store the value 
    */
   pNode = NewNode(value);
   if ( pNode == NULL ) {
      printf("list_add_front: failed to create a new node\n");

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
      printf("list_add_front: (first) node [%p] pHead [%p] pTail[%p]\n", (void*)pNode, (void*)p->pHead, (void*)p->pTail);
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
 * @fn        int list_add_back ( list_t *p, int value ) 
 *
 * @brief     Adds a node to the back of the list
 * 
 * @param[in] *p    - Pointer to the list
 * @param[in] value - to add
 *
 * @return    none
 */
int list_add_back ( list_t *p, int value ) {
   node_t *pTemp = NULL; 
   node_t *pCurrentTail;
   
   /* 
    * Create new "back" element
    */
   pTemp = NewNode(value);
   pCurrentTail = GetListTail(p);  /* Get the current Tail element                   */
   pCurrentTail->pNext = pTemp;    /* Current Tail points to the new element created */
   p->pTail = pTemp;               /* Advances the Tail to the new Tail elemenet     */

   p->NodeCount++;                 /* Increase the number of nodes                   */

   return SUCCESS;
}

/**
 * @fn        void list_add_position( list_t *p, int position, int value)
 *
 * @brief     Adds a node to a list at 'Position'
 * 
 * @param[in] *p       - Pointer to the list
 * @param[in] position - place to add
 * @param[in] value    - to add
 *
 * @return    none
 */
int list_add_position( list_t *p, int position, int value ) {
   node_t *pTemp = NULL; 
   node_t *pCurrent;
   node_t *pPrevious;   
   int i;

   if ( position > list_size(p)) {
     printf("list_add_position: position is beyond end of the list\n");

     return ERROR_LIST_BAD_POSITION;
   }

   if (position == 0) {
     list_add_front(p,value);

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
  
   p->NodeCount++;                 /* Increase the number of nodes                   */

   return SUCCESS;
}

/**
 * @fn        int  list_get_position(list_t *p, int position) 
 *
 * @brief     Return an element value given a position in the list
 * 
 * @param[in] *p   - Pointer to the list
 * @param[in] position of element in the list
 *
 * @return    int  - Value at the list position or -1 if empty
 */
int  list_get_position(list_t *p, int position) {
  node_t *pCurrent;
  int value = 0;
  int i;
  
  if (list_empty(p)) {
     printf("list_get_position - list is empty");

     return ERROR_LIST_EMPTY;
  }

  /*
   * Traverse the list until we get to position
   */
  pCurrent = GetListHead(p);  /* Start of the list */
  for (i=1; i < position; i++) {
     pCurrent = pCurrent->pNext;
  }

  value = pCurrent->value;

  return value;
}

/**
 * @fn        int  list_get_front   (list_t *p)
 *
 * @brief     Return the value at the front of the list
 * 
 * @param[in] *p   - Pointer to the list
 *
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
 *
 * @brief     return the value at the back of the list
 * 
 * @param[in] *p   - Pointer to the list
 *
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
 *
 * @brief     Returns the size or number of nodes in a list
 * 
 * @param[in] *p   - Pointer to the list
 *
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
 * @fn        int list_delete_element(list_t *p, int position) 
 * @brief     delete a given element at 'position'
 *
 * @param[in] *p    Pointer to the list to delete
 * @param[in] position in the list
 * @return    none
 *
 * @note      
 */
int list_delete_element(list_t *p, int position) {
  node_t *pCurrent;
  node_t *pPrevious;

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
      }
      pPrevious->pNext = pCurrent->pNext;    /* Previous entry is now pointing to one beyond the deleted entry */      
  }
  free(pCurrent);                            /* Delete the node                                                */
  p->NodeCount--;                            /* Decrement the node count                                       */

  return SUCCESS;
}

/**
 * @fn        int list_delete_front(list_t *p)
 * @brief     delete the Front element
 *
 * @param[in] *p    Pointer to the list to delete the element
 *
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
 *
 * @param[in] *p    Pointer to the list to delete
 *
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
       return ERROR_LIST_EMPTY;
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
 */
void list_reverse ( list_t *p ) {
  node_t *pCurrent = NULL;
  node_t *pNext    = NULL;
  node_t *pPrevious= NULL;

  if (list_size(p) == 0) {
    printf("list_reverse: Empty!\n");

    /*    Thrower(e_empty); */
    
    return;
  }

  pCurrent = GetListHead(p);              /* Point to start of the list         */
#if 0  
  p->pTail = p->pHead;                    /* Swap the tail to point to the head */
#endif  
  printf("pCurrent %p\n",(void*)pCurrent);  
  while ( pCurrent != NULL ) {
    pNext = pCurrent->pNext;
    printf("pNext %p\n", (void*)pNext);
    pCurrent->pNext = pPrevious;
    pPrevious = pCurrent;
  printf("pCurrent->next %p\n",(void*)pCurrent->pNext);      
    pCurrent = pNext;
  printf("pCurrent %p\n",(void*)pCurrent);      
  }

  p->pHead = pPrevious;
  printf("pHead %p\n",(void*)p->pHead);    
}

/**
 * @fn     void list_show ( list_t *p )
 * @brief  Display items in the list
 * @param  *p - pointer to list
 * @return none
 */
void list_show ( list_t *p ) {
  node_t *pCurrent = NULL;
  
  if (!list_empty(p)) {
    int Count = 0;

    printf("      Address   \tValue\t   pNext\t#Nodes [%d] pHead [%p] pTail [%p]\n",
	   p->NodeCount,
	   (void *)p->pHead,
	   (void *)p->pTail);
  
    pCurrent = GetListHead(p);
    while (pCurrent) {
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
    }
  } else {
    printf("\t#Nodes [%d] pHead [%p] pTail [%p]\n",
	   p->NodeCount,
	   (void *)p->pHead,
	   (void *)p->pTail);
  }
}

