#include <stdio.h>          // printf()
#include <string.h>         // strcpy()
#include <stdlib.h>         // malloc()

#include "cut.h"

#define CUT_VERSION "0.0.5"
#define MAX_TESTS 1000

cut_test_t tests[MAX_TESTS];
static int cutTestIndex = 0;

/**
 * Register a test with cut; this is necessary for the test to be run by the framework.
 */
void register_test(void (*f)(cut_run_t *), char * name)
{
    /* create a test instance; this will be stored internally */
    cut_test_t test;

    /* set fields in the test */
    test.test = f;
    test.name = malloc(sizeof(char) * strlen(name));                                    // todo: handle malloc() failure
    strcpy(test.name, name);

    /* store the test */
    tests[cutTestIndex] = test;

    /* increment the current index */
    cutTestIndex += 1;
}

/**
 * Run all tests registered with cut.
 */
int run_tests(cut_config_t * config)
{
    /* storage for the number of failed tests; initially, zero */
    int test_function_count = 0;
    int total = 0;
    int failed = 0;
    int succeeded = 0;

    /* store run information */
    cut_run_t runs[MAX_TESTS];

    /* loop over all registered tests; number is equal to the current index, minus 1 */
    for (int c = 0; c < cutTestIndex; c++)
    {
        /* create a test run; values are initially zero */
        cut_run_t run = {.total_successful=0, .total_failed=0};

        /* get the test instance */
        cut_test_t test = tests[c];

        /* copy the test name over */
        run.name = malloc(sizeof(strlen(test.name)));
        strcpy(run.name, test.name);

        /* run the test instance */
        (*test.test)(&run);

        /* update total counts */
        succeeded += run.total_successful;
        failed += run.total_failed;
        total += run.total_successful + run.total_failed;
        test_function_count++;

        /* store the run for printing later */
        runs[c] = run;
    }

    /* print end summary, if requested */
    if (config->print_summary)
    {
        printf("unit test summary - cut v%s\n", CUT_VERSION);
        for (int c = 0; c < test_function_count; c++)
        {
            cut_run_t run = runs[c];
            printf("\t%s: %s\n", run.name, run.total_failed > 0 ? "failed" : "succeeded");
        }
        printf("%d tests; %d succeeded, %d failed\n", total, succeeded, failed);
    }

    /* done; return the failed count */
    return failed;
}

/**
 * Assert that the given value is true.
 */
void assert_true(bool assertion, cut_run_t * run)
{
    if (assertion)
    {
        run->total_successful += 1;
    } else {
        run->total_failed += 1;
    }
}
