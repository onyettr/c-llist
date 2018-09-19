/*
 *****************************************************************************
 *! \file 
 *
 * MODULE: C Programming Examples
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
 * PURPOSE: 
 * Header file for simple linked list management library
 *
 * Two main datastructures here List_t and Node_t.
 *     List_t                  node_t              node_t
 *    pFront   ------------>   value               value
 *    pTail    ------------|   pNext ------------> pNext
 *                         |                         ^
 *                         |                         |
 *                         ---------------------------
 *
 * Operations
 * - Create a list
 * - Add to list. This will grow the list from pTail
 * - Add to front. This will add a node a the pFront of the List
 * - Delete list, this will free() all nodes and then free the List_t header.
 * - Reverse list
 * - Show. This will dump the List and all nodes
 * - Search list. Given a value it searches for it.
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
#ifndef __LIST_H__
#define __LIST_H__

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

/**
 * \struct Node
 * \brief  Data structure to hold the an "element" 
 */
typedef struct node { 
  struct node *pNext;     /* Next node */
  struct node *pPrev;     /* Prev node */
  void *pData;            /* data to carry */
  int value;              /* storage   */
} node_t;

/**
 * \struct list
 * \brief  Root list header for nodes
 */
typedef struct list {
  node_t *pFront;         /* Pointer to Front node */
  node_t *pHead;
  node_t *pTail;          /* Pointer to Tail node  */
  int  NodeCount;         /* Nodes per list        */
} list_t;

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

extern list_t *list_create(void);
extern void list_delete( list_t *p );
extern int  list_add ( list_t *p, int value );
extern void list_add_front ( list_t *p, int value );
extern void list_reverse ( list_t *p );
extern void list_show ( list_t *p );
extern node_t *list_search_value(list_t *p, int value);

#endif /* __LIST_H__ */

