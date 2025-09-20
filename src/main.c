#include <stdio.h>

#include "add.h"
#include "version.h"

int main(int argc, char * argv[])
{
    /* print version info, if requested */
    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'v')
    {
            printf("add demo, version: %s\n", VERSION);
            return 0;
    }

    /* addends; these could come from command line */
    int leftAddend = 2;
    int rightAddend = 3;

    /* print result of add */
    printf("add: %i+%i=%i", leftAddend, rightAddend, add(leftAddend, rightAddend));

    /* no errors */
    return 0;
}
