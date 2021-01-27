#!/bin/bash
gcc -std=c99 -pedantic -Oz -Wall -otests utilities.c accent.c tests.c 
./tests
