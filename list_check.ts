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
#tcase list_push
#

#test list_push_front_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "positive create failed");   

    fail_unless(list_push_front(lp, 101) == 0, "add no failure");
    fail_unless(list_get_front(lp) == 101, "push front failure");

#test list_push_back_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "positive create failed");  
    list_add_element(lp,201);
    list_add_element(lp,301);    
    fail_unless(list_push_back(lp, 111) == 0, "add no failure");
    fail_unless(list_get_back(lp) == 111, "push back failure");

#test list_push_back_positive_empty
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "positive create failed");  
    fail_unless(list_push_back(lp, 111) == 0, "add no failure");
    fail_unless(list_get_back(lp) == 111, "push back failure");

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
    list_push_front(lp,111);    
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
    list_push_back  (lp,111);
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
    fail_unless(list_get_position(lp,1) == 301, "get position fails");
#
#tcase list_clear
#

# test list_clear_negative_list_empty
     list_t *lp;
     lp = NULL;
     fail_unless(list_clear(lp) == ERROR_LIST_EMPTY, "list clear: list is empty (NULL)");

# test list_clear_postitve_list_populated
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_add_element(lp, 302) == SUCCESS, "add no failure");
     fail_unless(list_add_element(lp, 403) == SUCCESS, "add no failure");
     fail_unless(list_add_element(lp, 504) == SUCCESS, "add no failure");
     fail_unless(list_add_element(lp, 605) == SUCCESS, "add no failure");     
     fail_unless(list_clear(lp) == SUCCESS, "list clear: ok");
//     fail_unless(list_size(lp) == 0,  "list clear: size not ok");
     
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

#tcase list_remove

# test list_remove_empty_list
  list_t *lp = NULL;
  lp = list_create();

  fail_unless(list_remove(lp,48) == ERROR_LIST_EMPTY, "assign failed");

# test list_remove_one_element
  list_t *rmTest = NULL;
  rmTest = list_create();

  list_add_element(rmTest,101);
  list_add_element(rmTest,201);
  list_add_element(rmTest,301);
  fail_unless(list_remove(rmTest,201) == SUCCESS, "remove single element");
  fail_unless(list_size(rmTest) == 2, "remove single element size");

# test list_remove_two_elements
  list_t *rmTest3 = NULL;
  rmTest3 = list_create();

  list_add_element(rmTest3,1001);
  list_add_element(rmTest3,2001);
  list_add_element(rmTest3,201);
  list_add_element(rmTest3,201);
  list_add_element(rmTest3,3001);
  list_add_element(rmTest3,4001);
  list_add_element(rmTest3,5001);
  list_add_element(rmTest3,6001);
  list_add_element(rmTest3,7001);  

  fail_unless(list_remove(rmTest3,201) == SUCCESS, "remove two elements");
  fail_unless(list_size(rmTest3) == 7, "remove two element size");  
  
# test list_remove_start_elements
  list_t *rmTest4 = NULL;
  rmTest4 = list_create();

  list_add_element(rmTest4,201);  
  list_add_element(rmTest4,1001);
  list_add_element(rmTest4,3001);
  
  fail_unless(list_remove(rmTest4,201) == SUCCESS, "remove start element");
  fail_unless(list_size(rmTest4) == 2, "remove start element size");
  fail_unless(list_get_front(rmTest4) == 1001, "remove start get element");

# test list_remove_back_elements
  list_t *rmTest5 = NULL;
  rmTest5 = list_create();

  list_add_element(rmTest5,1001);
  list_add_element(rmTest5,3001);
  list_add_element(rmTest5,201);  
  list_show(rmTest5);

  fail_unless(list_remove(rmTest5,201) == SUCCESS, "remove end element");
  fail_unless(list_size(rmTest5) == 2, "remove end element size");
  fail_unless(list_get_back(rmTest5) == 3001, "remove end get element");

# test list_remove_numerous_elements
  list_t *rmTest6 = NULL;
  rmTest6 = list_create();

  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,1001);
  list_add_element(rmTest6,2001);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,3001);

  fail_unless(list_remove(rmTest6,201) == SUCCESS, "remove numerous elements");
  fail_unless(list_size(rmTest6) == 3, "remove numerous element size");  
  fail_unless(list_get_front(rmTest6) == 1001, "remove numerous get element");

#tcase list_remove_if

bool is_odd (int value) {
  return (value%2) == 1;  
}

# test list_remove_if_empty_list
  list_t *lp = NULL;
  lp = list_create();

  fail_unless(list_remove(lp,48) == ERROR_LIST_EMPTY, "assign failed");

# test list_remove_if_one_element
  list_t *rmTest = NULL;
  rmTest = list_create();

  list_add_element(rmTest,100);
  list_add_element(rmTest,201);
  list_add_element(rmTest,300);
  fail_unless(list_remove_if(rmTest,is_odd) == SUCCESS, "remove single element");
  fail_unless(list_size(rmTest) == 2, "remove single element size");

# test list_remove_if_two_elements
  list_t *rmTest3 = NULL;
  rmTest3 = list_create();

  list_add_element(rmTest3,100);
  list_add_element(rmTest3,200);
  list_add_element(rmTest3,201);
  list_add_element(rmTest3,201);
  list_add_element(rmTest3,300);
  list_add_element(rmTest3,400);
  list_add_element(rmTest3,500);
  list_add_element(rmTest3,600);
  list_add_element(rmTest3,700);  

  fail_unless(list_remove_if(rmTest3,is_odd) == SUCCESS, "remove two elements");
  fail_unless(list_size(rmTest3) == 7, "remove two element size");  
  
# test list_remove_if_start_elements
  list_t *rmTest4 = NULL;
  rmTest4 = list_create();

  list_add_element(rmTest4,201);  
  list_add_element(rmTest4,100);
  list_add_element(rmTest4,300);
  
  fail_unless(list_remove_if(rmTest4,is_odd) == SUCCESS, "remove start element");
  fail_unless(list_size(rmTest4) == 2, "remove start element size");
  fail_unless(list_get_front(rmTest4) == 100, "remove start get element");

# test list_remove_if_back_elements
  list_t *rmTest5 = NULL;
  rmTest5 = list_create();

  list_add_element(rmTest5,100);
  list_add_element(rmTest5,300);
  list_add_element(rmTest5,201);  
  list_show(rmTest5);

  fail_unless(list_remove_if(rmTest5,is_odd) == SUCCESS, "remove end element");
  fail_unless(list_size(rmTest5) == 2, "remove end element size");
  fail_unless(list_get_back(rmTest5) == 300, "remove end get element");

# test list_remove_if_numerous_elements
  list_t *rmTest6 = NULL;
  rmTest6 = list_create();

  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,100);
  list_add_element(rmTest6,200);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);
  list_add_element(rmTest6,201);    
  list_add_element(rmTest6,300);

  fail_unless(list_remove_if(rmTest6,is_odd) == SUCCESS, "remove numerous elements");
  fail_unless(list_size(rmTest6) == 3, "remove numerous element size");  
  fail_unless(list_get_front(rmTest6) == 100, "remove numerous get element");





  