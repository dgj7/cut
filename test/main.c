#include <stdio.h>

#include "cut.h"
#include "test_add.h"

int main() {
    register_test(test1, "test1");
    register_test(test2, "test2");
    register_test(test3, "test3");
    register_test(test4, "test4");

    return run_tests();
}
