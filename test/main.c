#include <stdio.h>

#include "cut.h"
#include "test_add.h"

int main()
{
    /* configure cut */
    cut_config_t config = {.print_summary = true};

    /* these tests pass */
    register_test(test1, "test1");
    register_test(test5, "test5");

    /* these tests fail; uncomment these tests to verify failure */
    //register_test(test2, "test2");
    //register_test(test3, "test3");
    //register_test(test4, "test4");

    /* return the number of failed tests */
    return run_tests(&config);
}
