#include "list.h"

#suite LinkedList

#tcase list_creation

#test list_create_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "list create failed");   

#tcase list_addition

#test list_add_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "positive create failed");   

    fail_unless(list_add(lp, 101) == 0, "add no failure");

#tcase list_deletion

# test list_delete_negative_list_empty
     list_t *lp;
     lp = NULL;
     fail_unless(list_delete(lp) == -1, "list deletion: list is empty (NULL)");

# test list_delete_postitve_list_populated
     list_t *lp = NULL;
     lp = list_create();
     fail_unless(lp != NULL, "list create failed");
     fail_unless(list_add(lp, 101) == 0, "add no failure");
     fail_unless(list_delete(lp) == 0, "list deletion: ok");     