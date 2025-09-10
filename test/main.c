#include <stdio.h>

#include "cut.h"
#include "test_add.h"

int main() {
    /* this test always passes */
    register_test(test1, "test1");

    /* uncomment these tests to verify failure */
    //register_test(test2, "test2");
    //register_test(test3, "test3");
    //register_test(test4, "test4");

    /* return the number of failed tests */
    return run_tests();
}
