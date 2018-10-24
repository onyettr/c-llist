/*
 *****************************************************************************
 * @file   list.h
 *
 * @brief  Header for list 
 * @detail Header file for simple linked list management library
 *
 * Two main datastructures here List_t and Node_t.
 *     List_t                  node_t              node_t
 *    pFront   ------------>   value               value
 *    pTail    ------------|   pNext ------------> pNext
 *                         |                         ^
 *                         |                         |
 *                         ---------------------------
 *
 * Operational APIs
 * - Create a list       creates the list_t type to hold count, Head and Tail
 * - Add to list.        This will grow the list from pTail with a new node_t
 * - Add to front.       This will add a node to the pFront of the List
 * - Add to position.    Add a new node to a 'position' within the list
 * - Delete list         This will free() all nodes and then free the List_t header.
 * - Delete element      Deletes a node at a given position
 * - Reverse list        Tail is now head, head is now tail
 * - Show List           This will dump the List and all nodes
 * - Search list         Given a value it searches for it and returns the node
 * - Get Front           Returns the head node of a given list
 * - Get Tail            Returns the Tail node of a given list
 * - Size                Returns the size of a given list i.e. number of nodes
 * - Empty               Returns if the list is Empty
 * - GetListHead         Returns the head of a given list
 * - HetListTail         Returns the head of a given list
 ***************************************************************************** 
 */

#ifndef __LIST_H__
#define __LIST_H__
/*
******************************************************************************
Includes
******************************************************************************
*/
#include <stdbool.h>

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
 * @struct Node
 * @brief  Data structure to hold the an "element" 
 */
typedef struct node { 
  struct node *pNext;     /* Next node */
  struct node *pPrev;     /* Prev node */
  void *pData;            /* data to carry */
  int value;              /* storage   */
} node_t;

/**
 * @struct list
 * @brief  Root list header for nodes
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

list_t *list_create(void);
int  list_delete( list_t *p );
int  list_add_element (list_t *p, int value );
void list_add_front   (list_t *p, int value );
void list_add_back    (list_t *p, int value );
void list_add_position(list_t *p, int position, int value );
void list_reverse     (list_t *p);
void list_show        (list_t *p);
int  list_get_position(list_t *p, int position); // return value at "position"
int  list_get_front   (list_t *p);         // return value of first list element
int  list_get_back    (list_t *p);         // return value of tail list element
void list_delete_element(list_t *p, int position); // Delete element  at position, decreases list size by 1  
void list_sort        (list_t *p);         // Sort the list
int  list_size        (list_t *p);         // Number of elements in the list
bool list_empty       (list_t *p);         // is the list empty?
node_t *list_search_value(list_t *p, int value);
node_t *GetListHead   (list_t *p);         // Obtain Head iterator pointing to first element
node_t *GetListTail   (list_t *p);        // Obtain Tail iterator pointing to last element

#endif /* __LIST_H__ */

