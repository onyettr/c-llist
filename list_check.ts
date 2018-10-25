#include "list.h"

#suite LinkedList

#
#tcase list_creation
#

#test list_create_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "list create failed");   

#
#tcase list_empty No elements
#
#test list_empty_positive_test01
    list_t *emptyTest;
    emptyTest = list_create();
    fail_unless(list_empty(emptyTest) == 1, "test01 list empty TRUE");

#
#tcase list_empty One element
#

#test list_empty_positive_test02
    list_t *lp;
    lp = list_create();
    list_add_element(lp,100);
    fail_unless(list_empty(lp) == 0, "test02 list empty TRUE");

#
#tcase list_size
#
#test list_size_empty
    list_t *lp;
    lp = list_create();
    fail_unless(list_size(lp) == 0, "test01 list size = 0");

#test list_size_not_empty
    list_t *lp;
    lp = list_create();
    list_add_element(lp,100);    
    fail_unless(list_size(lp) == 1, "test01 list size = 0");

#
#tcase list_addition
#

#test list_add_element_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "positive create failed");   

    fail_unless(list_add_element(lp, 101) == 0, "add no failure");

#
#tcase list_get_front
#
#test list_get_front_empty_list
    list_t *lp;
    lp = list_create();
    fail_unless(list_get_front(lp) == -1, "get front empty list no failure");    

#test list_get_front_one_element_list
    list_t *lp;
    lp = list_create();
    list_add_element(lp,200);
    fail_unless(list_get_front(lp) == 200, "get front one element list no failure");    

#test list_get_front_two_element_list
    list_t *lp;
    lp = list_create();
    list_add_element(lp,200);
    list_add_element(lp,300);    
    fail_unless(list_get_front(lp) == 200, "get front two element list no failure");    

#test list_get_front_new_front_element
    list_t *lp;
    lp = list_create();
    list_add_element(lp,200);
    list_add_element(lp,300);
    list_add_front(lp,111);    
    fail_unless(list_get_front(lp) == 111, "get front new front element list no failure");    

#
#tcase list_deletion
#

# test list_delete_negative_list_empty
     list_t *lp;
     lp = NULL;
     fail_unless(list_delete(lp) == -1, "list deletion: list is empty (NULL)");

# test list_delete_postitve_list_populated
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_add_element(lp, 101) == 0, "add no failure");
     fail_unless(list_delete(lp) == 0, "list deletion: ok");     