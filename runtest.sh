#!/bin/bash
gcc -std=c99 -pedantic -Oz -Wextra -otests utilities.c accent.c tests.c 
# gcc -std=c99 -pedantic -Oz -Wextra -osplicetests utilities.c accent.c splicetest.c 
./tests
# ./splicetests
