#include <stdio.h>
#include "accent.h"

 int main(int v, char **a)
 {

 	UCS2 s[] = {0x03B1, 0x03B1, 0x0345};
 	int len1 = stripDiacritics(s, 3);

 	printf("test: %d\n", len1);//accentSyllableUtf8("ω", 1, 1) );

 	UCS2 s2[] = {0x03B1, 0x0345};
 	int len2 = stripDiacritics(s2, 2);

    printf("test: %d\n", len2);//accentSyllableUtf8("ω", 1, 1) );
 }
 