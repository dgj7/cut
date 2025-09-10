#ifndef C__UNIT__TESTS__H__
#define C__UNIT__TESTS__H__

#include <stdbool.h>                                            // bool data type

/**
 * A single run of a single test.
 */
typedef struct {
    int total_successful;
    int total_failed;
} cut_run_t;

/**
 * Definition of a test, with the test function to be called.
 */
typedef struct {
    char * name;
    void (*test)(cut_run_t *);
} cut_test_t;

void register_test(void (*f)(cut_run_t *), char * name);

int run_tests();

void assert_true(bool assertion, cut_run_t * run);

#endif
