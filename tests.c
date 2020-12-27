#include <stdio.h>
#include <assert.h>
#include "accent.h"
#include "GreekUnicode.h"

int main(int argc, char **argv)
{
	UCS2 buf[1024];
/*
 	UCS2 s[] = {0x03B1, 0x03B1, 0x0345};
 	int len1 = stripDiacritics(s, 3);

 	printf("test: %d\n", len1);//accentSyllableUtf8("ω", 1, 1) );

 	UCS2 s2[] = {0x03B1, 0x0345};
 	int len2 = stripDiacritics(s2, 2);

    printf("test: %d\n", len2);//accentSyllableUtf8("ω", 1, 1) );



    int len = 0;
    bool l = makeLetter((UCS2*)&buf, &len, 0x03B1, _ACUTE, PRECOMPOSED_WITH_PUA_MODE);
    printf("letter %04x %d, %d\n", buf[0], len, l);

    buf[0] = 0x03B1;
    int x = accentSyllable2((UCS2*)&buf, 1, ACUTE, true, PRECOMPOSED_WITH_PUA_MODE);
	printf("letter2: %04x %d\n", buf[0], x);
*/
	    
	//α == α
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == 0 );

   	//α == ά
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA_WITH_TONOS;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == 0);

   	//α + COMBINING_ACUTE == ά
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_ACUTE;
   	buf[2] = GREEK_SMALL_LETTER_ALPHA_WITH_TONOS;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 1, _HK_COMP_INSENSITIVE) == 0);

   	//α < αβ
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = GREEK_SMALL_LETTER_BETA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 2, _HK_COMP_INSENSITIVE) == -1);

   	//αβ > β
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = GREEK_SMALL_LETTER_BETA;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == -1);

   	//αβ > α
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = GREEK_SMALL_LETTER_BETA;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[0], 1, _HK_COMP_INSENSITIVE) == 1);

   	//αβ > α
   	buf[0] = GREEK_SMALL_LETTER_SIGMA;
   	buf[1] = GREEK_SMALL_LETTER_FINAL_SIGMA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == 0);

   	//α > α
   	buf[0] = GREEK_SMALL_LETTER_SIGMA;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA;
   	buf[2] = GREEK_SMALL_LETTER_FINAL_SIGMA;
   	buf[3] = GREEK_SMALL_LETTER_BETA;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_INSENSITIVE) == -1);

   	//EB09
   	//α > α
   	buf[0] = 0xEB09;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == 0);


   	//α == ά
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA_WITH_TONOS;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_DIA_SENSITIVE) == 1);

   	//α + COMBINING_ACUTE == ά
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_ACUTE;
   	buf[2] = GREEK_SMALL_LETTER_ALPHA_WITH_TONOS;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 1, _HK_COMP_DIA_SENSITIVE) == 0);

   	//α + COMBINING_ACUTE != combining_grave not match
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_ACUTE;
   	buf[2] = GREEK_SMALL_LETTER_ALPHA;
   	buf[3] = COMBINING_GRAVE;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_DIA_SENSITIVE) == 1);

   	//α + COMBINING_ACUTE == combining grave insensitive
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_ACUTE;
   	buf[2] = GREEK_SMALL_LETTER_ALPHA;
   	buf[3] = COMBINING_GRAVE;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_INSENSITIVE) == 0);

   	//α + COMBINING_Grave != precomposed tonos
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_GRAVE;
   	buf[2] = GREEK_SMALL_LETTER_ALPHA_WITH_TONOS;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 1, _HK_COMP_DIA_SENSITIVE) == 1);

   	//PUA and combining sensitive match
   	buf[0] = 0xEB09;
   	buf[1] = COMBINING_IOTA_SUBSCRIPT;

   	buf[2] = GREEK_SMALL_LETTER_ALPHA;
   	buf[3] = COMBINING_MACRON;
   	buf[4] = COMBINING_ROUGH_BREATHING;
   	buf[5] = COMBINING_ACUTE;
   	buf[6] = COMBINING_IOTA_SUBSCRIPT;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 5, _HK_COMP_DIA_SENSITIVE) == 0);

   	//PUA and combining sensitive not match
   	buf[0] = 0xEB09;
   	buf[1] = COMBINING_IOTA_SUBSCRIPT;
   	
   	buf[2] = GREEK_SMALL_LETTER_ALPHA;
   	buf[3] = COMBINING_MACRON;
   	buf[4] = COMBINING_ROUGH_BREATHING;
   	buf[5] = COMBINING_GRAVE;
   	buf[6] = COMBINING_IOTA_SUBSCRIPT;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 5, _HK_COMP_DIA_SENSITIVE) == 1);

   	//PUA and combining insensitive
   	buf[0] = 0xEB09;
   	buf[1] = COMBINING_IOTA_SUBSCRIPT;
   	
   	buf[2] = GREEK_SMALL_LETTER_ALPHA;
   	buf[3] = COMBINING_MACRON;
   	buf[4] = COMBINING_ROUGH_BREATHING;
   	buf[5] = COMBINING_GRAVE;
   	buf[6] = COMBINING_IOTA_SUBSCRIPT;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 5, _HK_COMP_INSENSITIVE) == 0);   	

   	//non-greek char with ignore unknown chars
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = 0x0030;
   	buf[2] = GREEK_SMALL_LETTER_BETA;

   	buf[3] = GREEK_SMALL_LETTER_ALPHA;
   	buf[4] = GREEK_SMALL_LETTER_BETA;
   	assert( compare((UCS2*)&buf[0], 3, (UCS2*)&buf[3], 2, _HK_COMP_DIA_SENSITIVE | _HK_IGNORE_UNKNOWN_CHARS) == 0);

   	//non-greek char withOUT ignore unknown chars
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = 0x0030;
   	buf[2] = GREEK_SMALL_LETTER_BETA;

   	buf[3] = GREEK_SMALL_LETTER_ALPHA;
   	buf[4] = GREEK_SMALL_LETTER_BETA;
   	assert( compare((UCS2*)&buf[0], 3, (UCS2*)&buf[3], 2, _HK_COMP_DIA_SENSITIVE) == 1);

   	//non-greek greater than basic greek range.
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = 0x0400;

   	buf[2] = GREEK_SMALL_LETTER_ALPHA;
   	buf[3] = 0x0400;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_DIA_SENSITIVE) == 1);

   	//non-greek greater than basic greek range.
   	buf[0] = GREEK_SMALL_LETTER_OMEGA;
   	buf[1] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == 0);

   	//space α == space α _HK_IGNORE_UNKNOWN_CHARS
   	buf[0] = 0x0030;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA;
   	buf[2] = 0x0030;
   	buf[3] = GREEK_SMALL_LETTER_ALPHA;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_INSENSITIVE | _HK_IGNORE_UNKNOWN_CHARS) == 0 );

   	//space α < space β _HK_IGNORE_UNKNOWN_CHARS
   	buf[0] = 0x0030;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA;
   	buf[2] = 0x0030;
   	buf[3] = GREEK_SMALL_LETTER_BETA;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_INSENSITIVE | _HK_IGNORE_UNKNOWN_CHARS) == -1 );

   	//space β > space α _HK_IGNORE_UNKNOWN_CHARS
   	buf[0] = 0x0030;
   	buf[1] = GREEK_SMALL_LETTER_BETA;
   	buf[2] = 0x0030;
   	buf[3] = GREEK_SMALL_LETTER_ALPHA;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_INSENSITIVE | _HK_IGNORE_UNKNOWN_CHARS) == 1 );

   	//space β != space α without _HK_IGNORE_UNKNOWN_CHARS
   	buf[0] = 0x0030;
   	buf[1] = GREEK_SMALL_LETTER_BETA;
   	buf[2] = 0x0030;
   	buf[3] = GREEK_SMALL_LETTER_ALPHA;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_INSENSITIVE) == 1 );

   	assert( compareUTF8("α", "αβ", _HK_COMP_DIA_SENSITIVE) == -1);
   	assert( compareUTF8("β", "α", _HK_COMP_DIA_SENSITIVE) == 1);
   	assert( compareUTF8("αβ", "α", _HK_COMP_DIA_SENSITIVE) == 1);
   	assert( compareUTF8("α", "αβ", _HK_COMP_DIA_SENSITIVE) == -1);
   	assert( compareUTF8("ω", "ὤ", _HK_COMP_DIA_SENSITIVE) == 1);
   	assert( compareUTF8("ω", "ὤ", _HK_COMP_INSENSITIVE) == 0);




   	printf("All tests passed\n");
}
