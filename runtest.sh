#!/bin/bash
gcc -std=c99 -pedantic -Oz -Wextra -otests utilities.c accent.c tests.c 
./tests
