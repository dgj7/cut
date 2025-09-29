#include <stdio.h>

#include "add.h"

int main(int argc, char * argv[])
{
    /* addends; these could come from command line */
    const int leftAddend = 2;
    const int rightAddend = 3;

    /* print result of add */
    printf("add: %i+%i=%i", leftAddend, rightAddend, add(leftAddend, rightAddend));

    /* no errors */
    return 0;
}
