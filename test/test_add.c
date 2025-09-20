#include <stdio.h>

#include "test_add.h"
#include "../src/add.h"
#include "cut.h"

/* both succeed */
void test1(cut_run_t * run)
{
    assert_true(2 == add(1, 1), run);
    assert_true(2 == add(1, 1), run);
}

/* first fails */
void test2(cut_run_t * run)
{
    assert_true(3 == add(1, 1), run);
    assert_true(2 == add(1, 1), run);
}

/* second fails */
void test3(cut_run_t * run)
{
    assert_true(2 == add(1, 1), run);
    assert_true(3 == add(1, 1), run);
}

/* both fail */
void test4(cut_run_t * run)
{
    assert_true(3 == add(1, 1), run);
    assert_true(3 == add(1, 1), run);
}
