#include <stdio.h>
#include "accent.h"

int main(int argc, char** argv) {
	
    size_t bufferCapacity = 1024;
    UCS2 buffer[bufferCapacity];
    size_t len = 0;
    
	char input; //this is promoted to a UCS2
    while ( scanf(" %c", &input) == 1 ) {
        len = 0;
        accentSyllable((UCS2*)buffer, &len, input, true, PRECOMPOSED_WITH_PUA_MODE);
        printf("result: %04X -> %04X\n", input, buffer[0]);
        buffer[0] = 0;
    }
}
