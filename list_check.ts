#include "list.h"

#test create_positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "positive create failed");   

#test list_add positive
    list_t *lp;
    lp = list_create();
    fail_unless(lp != NULL, "positive create failed");   

    fail_unless(list_add(lp, 101) == 0, "add no failure");
    