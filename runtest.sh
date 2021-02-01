#!/bin/bash
gcc -std=c99 -pedantic -Oz -Wall -Wextra -Wno-unused-parameter -otests utilities.c accent.c tests.c 
# gcc -std=c99 -pedantic -Oz -Wextra -osplicetests utilities.c accent.c splicetest.c 
./tests
# ./splicetests
