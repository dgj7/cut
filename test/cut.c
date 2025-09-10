#include <stdio.h>          // printf()
#include <string.h>         // strcpy()
#include <stdlib.h>         // malloc()

#include "cut.h"

cut_test_t tests[1000];
static int index = 0;

/**
 * Register a test with cut; this is necessary for the test to be run by the framework.
 */
void register_test(void (*f)(cut_run_t *), char * name) {
    /* create a test instance; this will be stored internally */
    cut_test_t test;

    /* set fields in the test */
    test.test = f;
    test.name = malloc(sizeof(char) * strlen(name));                                    // todo: handle malloc() failure
    strcpy(test.name, name);

    /* store the test */
    tests[index] = test;

    /* increment the current index */
    index += 1;
}

/**
 * Run all tests registered with cut.
 */
int run_tests() {
    /* storage for the number of failed tests; initially, zero */
    int failed = 0;

    /* loop over all registered tests; number is equal to the current index, minus 1 */
    for (int c = 0; c < index; c++) {
        /* create a test run; values are initially zero */
        cut_run_t run = {.total_successful=0, .total_failed=0};

        /* get the test instance */
        cut_test_t test = tests[c];

        /* run the test instance */
        (*test.test)(&run);

        /* update the failed count with the failed count from the test run */
        failed += run.total_failed;

        /* print test summary */
        printf("%s: %s\n", test.name, run.total_failed > 0 ? "failed" : "succeeded");       // todo: make configurable, to potentially not print if not requested?
    }

    /* done; return the failed count */
    return failed;
}

/**
 * Assert that the given value is true.
 */
void assert_true(bool assertion, cut_run_t * run) {
    if (assertion) {
        run->total_successful += 1;
    } else {
        run->total_failed += 1;
    }
}
