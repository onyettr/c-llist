/**
 *****************************************************************************
 * MODULE: C Programming Examples
 *
 * @author onyettr
 * PURPOSE: unity test harness for Simple List
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
#include "unity.h"

/** 
 * testcase: List creation
 */

void list_create_positive(void) {
  list_t *lp;

  lp = list_create();
  TEST_ASSERT_MESSAGE(lp != NULL, "Failed: List returned NULL");
}

void list_create_fixed_positive(void) {
    list_t *lp;

    lp = list_create_fixed(4);
    TEST_ASSERT_MESSAGE(lp != NULL, "Failed: List returned NULL");
    TEST_ASSERT_MESSAGE(list_size(lp) == 4, "list create fixed failed");       
}

void list_create_fill_positive(void) {
    list_t *lp;

    lp = list_create_fill(5,202);
    TEST_ASSERT_MESSAGE(lp != NULL, "Failed: list returned NULL");
    TEST_ASSERT_MESSAGE(list_size(lp) == 5, "list create fill failed on size");       
    TEST_ASSERT_MESSAGE(list_get_back(lp) == 202, "list create fill failed on element return");
}    

/**
 * testcase: List Empty
 */
void list_empty_positive(void) {
    list_t *emptyTest;

    emptyTest = list_create();
    TEST_ASSERT_MESSAGE(list_empty(emptyTest) == 1, "list empty TRUE");
}

void list_empty_one_element(void) {
    list_t *lp;

    lp = list_create();
    list_add_element(lp,100);

    TEST_ASSERT_MESSAGE(list_empty(lp) == 0, "list empty TRUE");
}

void runTest(UnityTestFunction test) {
  if(TEST_PROTECT()) {
    test();
  }
}

void setUp(void) {
}

void tearDown(void) {
}

int main ( void ) {
  UnityBegin("list.c");
  
  RUN_TEST(list_create_positive,          __LINE__);
  RUN_TEST(list_create_fixed_positive,    __LINE__);
  RUN_TEST(list_create_fill_positive,     __LINE__);    
  RUN_TEST(list_empty_positive,           __LINE__);
  RUN_TEST(list_empty_one_element,        __LINE__);
  
  UnityEnd();

  return 0;
}
