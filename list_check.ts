#include "list.h"

#suite LinkedList

#
#tcase list_creation
#

#test list_create_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "list create failed");   

#test list_create_fixed_positive
    list_t *lp;
    lp = list_create_fixed(4);
    fail_unless(lp != NULL, "list create fixed failed");
    fail_unless(list_size(lp) == 4, "list create fixed failed");       

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
    fail_unless(list_get_front(lp) == ERROR_LIST_EMPTY, "get front empty list no failure");    

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
#tcase list_get_back
#
#test list_get_back_empty_list
    list_t *lp;
    lp = list_create();
    fail_unless(list_get_back(lp) == ERROR_LIST_EMPTY, "get back empty list no failure");    

#test list_get_back_one_element_list
    list_t *lp;
    lp = list_create();
    list_add_element(lp,201);
    fail_unless(list_get_back(lp) == 201, "get back one element list no failure");    

#test list_get_back_two_element_list
    list_t *lp;
    lp = list_create();
    list_add_element(lp,201);
    list_add_element(lp,301);    
    fail_unless(list_get_back(lp) == 301, "get back two element list no failure");    

#test list_get_back_new_back_element
    list_t *lp;
    lp = list_create();
    list_add_element(lp,201);
    list_add_element(lp,301);
    list_add_back   (lp,111);
    list_show       (lp);
    fail_unless(list_get_back(lp) == 111, "get back new back element list no failure");    

#tcase list_get_position

# test list_get_position_empty
    list_t *lp;
    lp = list_create();
    fail_unless(list_get_position(lp,1) == ERROR_LIST_EMPTY, "get position empty fails");


# test list_get_position_too_big
    list_t *lp;
    lp = list_create();
    list_add_element(lp,201);
    list_add_element(lp,301);
    fail_unless(list_get_position(lp,5) == ERROR_LIST_BAD_POSITION, "get position bad fails");

# test list_get_position_postive
    list_t *lp;
    lp = list_create();
    list_add_element(lp,201);
    list_add_element(lp,301);
    fail_unless(list_get_position(lp,2) == 301, "get position fails");
#
#tcase list_deletion
#

# test list_delete_negative_list_empty
     list_t *lp;
     lp = NULL;
     fail_unless(list_delete(lp) == ERROR_LIST_EMPTY, "list deletion: list is empty (NULL)");

# test list_delete_postitve_list_populated
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_add_element(lp, 101) == 0, "add no failure");
     fail_unless(list_delete(lp) == 0, "list deletion: ok");

# test list_delete_front_positive
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_add_element(lp, 101) == 0, "add no failure");
     fail_unless(list_add_element(lp, 102) == 0, "add no failure");
     fail_unless(list_delete_front(lp) == SUCCESS, "list_deletion: list empty");
     fail_unless(list_get_front(lp) == 102, "list_get_front: fail");

# test list_delete_back_negative_no_elements_1B
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_delete_back(lp) == ERROR_LIST_EMPTY, "list_deletion: list is not empty");     

# test list_delete_back_positive_one_element_1C
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_add_element(lp, 200) == 0, "add no failure");     
     fail_unless(list_delete_back(lp) == 0, "list_delete_back: list fail");     

# test list_delete_back_positive_1A
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_add_element(lp, 101) == 0, "add failure");
     fail_unless(list_add_element(lp, 102) == 0, "add failure");
     fail_unless(list_add_element(lp, 103) == 0, "add failure");
     fail_unless(list_delete_back(lp) == SUCCESS, "list_deletion failed");
     fail_unless(list_get_back(lp) == 102, "list_get_back: fail");     

#
#tcase list_reverse
#

# test list_reverse_negative_empty_list
    list_t *lp = NULL;
    lp = list_create();
    fail_unless(list_reverse(lp) == ERROR_LIST_EMPTY, "reverse failure");
    
# test list_reverse_positive_one_element
    list_t *lp = NULL;
    lp = list_create();
    list_add_element(lp, 1);
    fail_unless(list_reverse(lp) == SUCCESS, "reverse fails");
    
# test list_reverse_positive_five_element
    list_t *lp = NULL;
    lp = list_create();   

    list_add_element(lp, 1);
    list_add_element(lp, 2);
    list_add_element(lp, 3);
    list_add_element(lp, 4);
    list_add_element(lp, 5);      
    list_show(lp);
    fail_unless(list_reverse(lp) == SUCCESS, "reverse failure");
    list_show(lp);  

#
#tcase list_assign
#

# test list_assign_empty_list
  list_t *lp = NULL;
  lp = list_create();

  fail_unless(list_assign(lp,7,100) == ERROR_LIST_EMPTY, "assign failed");

# test list_assign_too_small
  list_t *lp = NULL;
  lp = list_create();

  list_add_element(lp,200);
  fail_unless(list_assign(lp,7,100) == ERROR_LIST_TOO_SMALL, "assign too small failed");

# test list_assign_positive
  list_t *assignTest = NULL;
  assignTest = list_create();
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);
  list_add_element(assignTest,200);  
  
  fail_unless(list_assign(assignTest,7,100) == SUCCESS, "assign positive failure");
  fail_unless(list_get_front(assignTest) == 100, "assign positive failure");  