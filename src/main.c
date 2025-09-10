#include <stdio.h>

#include "add.h"

int main() {
    int leftAddend = 2;
    int rightAddend = 3;

    printf("add: %i+%i=%i", leftAddend, rightAddend, add(leftAddend, rightAddend));

    return 0;
}
