/**
 *****************************************************************************
 * @file    list.h
 * @brief   Header for list 
 * @details Header file for simple linked list management library
 *
 * Two main datastructures here List_t and Node_t.
 *     List_t                  node_t              node_t
 *    pFront   ------------>   value               value
 *    pTail    ------------|   pNext ------------> pNext ---> NULL
 *                         |                         ^
 *    NodeCount=2          |                         |
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
 * - Get Front           Returns the head node value of a given list
 * - Get Tail            Returns the Tail node value of a given list
 * - Size                Returns the size of a given list i.e. number of nodes
 * - Empty               Returns if the list is Empty
 * - GetListHead         Returns the head of a given list
 * - GetListTail         Returns the tail of a given list
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
 * @struct Node_t
 * @brief  Data structure to hold the an "element" 
 */
typedef struct node { 
  struct node *pNext;     /* Next node */
  struct node *pPrev;     /* Prev node */
  void *pData;            /* data to carry */
  int value;              /* storage   */
} node_t;

/**
 * @struct list_t
 * @brief  Root list header for a created list
 */
typedef struct list {
  node_t *pFront;         
  node_t *pHead;          /* Pointer to Front node               */
  node_t *pTail;          /* Pointer to Tail node                */
  int  NodeCount;         /* Number of Nodes in this list        */
} list_t;

/*
******************************************************************************
Private Macros
******************************************************************************
*/
#define SUCCESS                           0
#define ERROR_LIST_EMPTY                -10
#define ERROR_LIST_ALLOCATION_FAILED    -11
#define ERROR_LIST_BAD_POSITION         -12
#define ERROR_LIST_TOO_SMALL            -13
#define ERROR_LIST_TOO_BIG              -14

/*
******************************************************************************
Global variables
******************************************************************************
*/

list_t *list_create(void);                                  // Create a new list
list_t *list_create_fixed(int n);                           // Create a new list of size n
int  list_assign      (list_t *p, int n, int value);        // Assign (fill) n elements to value
int  list_add_element (list_t *p, int value);               // Add an element to the list, increases list size by 1
int  list_add_front   (list_t *p, int value);               // Add an element to the front of the list, increase list size by 1
int  list_add_back    (list_t *p, int value);               // Add an element to the back  of the list, increase list size by 1
int  list_add_position(list_t *p, int position, int value); // Add an element at position, increase list size by 1
int  list_reverse     (list_t *p);                          // Reverse the contents of the list
void list_show        (list_t *p);                          // Show the contents of the linked list
int  list_get_position(list_t *p, int position);            // return value at "position"
int  list_get_front   (list_t *p);                          // return value of first list element
int  list_get_back    (list_t *p);                          // return value of tail list element
int  list_delete_element(list_t *p, int position);          // Delete element  at position, decreases list size by 1
int  list_delete_front(list_t *p);                          // Delete element at the Front
int  list_delete_back (list_t *p);                          // Delete element at the Back
void list_sort        (list_t *p);                          // Sort the list
int  list_size        (list_t *p);                          // Number of elements in the list
bool list_empty       (list_t *p);                          // is the list empty?
int  list_clear       (list_t *p);                          // Remove all list elements 
int  list_search      (list_t *p, int value);               // Search list for value
int  list_remove      (list_t *p, int value);               // Remove elements of 'value' from list
node_t *GetListHead   (list_t *p);                          // Obtain Head iterator pointing to first element
node_t *GetListTail   (list_t *p);                          // Obtain Tail iterator pointing to last element

#endif /* __LIST_H__ */

