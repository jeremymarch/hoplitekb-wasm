#!/bin/bash
gcc -std=c99 -pedantic -Oz -Wall -Wextra -Wno-unused-parameter -otests utilities.c accent.c tests.c && ./tests
# gcc -std=c99 -pedantic -Oz -Wextra -osplicetests utilities.c accent.c splicetest.c 

# ./splicetests
