#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "accent.h"
#include <limits.h>
#include "GreekUnicode.h"

int main(int argc, char **argv)
{
	UCS2 buf[1024];
	size_t len = 0;
   	size_t bufferLen2 = 0;
   	size_t bufferCapacity = 1024;
   	UCS2 buf2[1024];


   	//this tests buffer capacity check.  
   	//here we convert only 2 rather than 3 characters because 
   	//buffer capacity is 2 + MAX_COMBINING (6) = 8
    buf[0] = GREEK_SMALL_LETTER_BETA;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA;
   	buf[2] = COMBINING_SMOOTH_BREATHING;
   	buf[3] = COMBINING_ACUTE;
   	buf[4] = COMBINING_IOTA_SUBSCRIPT;
   	buf[5] = GREEK_SMALL_LETTER_GAMMA;
   	len = 6;
   	bufferLen2 = 0;
   	bufferLen2 = convertString((UCS2*)buf, len, (UCS2*)buf2, 8, PRECOMPOSED_MODE);
   	assert (bufferLen2 == 2);
   	assert (memcmp(buf2, (UCS2[]){GREEK_SMALL_LETTER_BETA, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI}, 2 * sizeof(UCS2) ) == 0);


  
    buf[0] = GREEK_SMALL_LETTER_BETA;
   	buf[1] = GREEK_SMALL_LETTER_ALPHA;
   	buf[2] = COMBINING_SMOOTH_BREATHING;
   	buf[3] = COMBINING_ACUTE;
   	buf[4] = COMBINING_IOTA_SUBSCRIPT;
   	buf[5] = GREEK_SMALL_LETTER_GAMMA;
   	len = 6;
   	bufferLen2 = 0;
   	bufferLen2 = convertString((UCS2*)buf, len, (UCS2*)buf2, bufferCapacity, PRECOMPOSED_MODE);
   	assert (bufferLen2 == 3);
   	assert (memcmp(buf2, (UCS2[]){GREEK_SMALL_LETTER_BETA, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_GAMMA}, 3 * sizeof(UCS2) ) == 0);

	

   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_MACRON;
   	buf[2] = COMBINING_SMOOTH_BREATHING;
   	buf[3] = COMBINING_ACUTE;
   	buf[4] = COMBINING_IOTA_SUBSCRIPT;
   	len = 5;
   	bufferLen2 = convertString((UCS2*)buf, len, buf2, bufferCapacity, PRECOMPOSED_WITH_PUA_MODE);
   	assert (bufferLen2 == 2);
   	assert (memcmp(buf2, (UCS2[]){PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_MACRON,COMBINING_IOTA_SUBSCRIPT}, 2*sizeof(UCS2) ) == 0);


   	buf[0] = PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_MACRON;
   	buf[1] = COMBINING_IOTA_SUBSCRIPT;
   	len = 2;
   	bufferLen2 = 0;
   	bufferLen2 = convertString((UCS2*)buf, len, (UCS2*)buf2, bufferCapacity, COMBINING_ONLY_MODE);
   	//printf("len: %d, %02X %02X\n", bufferLen2, buf2[0], buf2[1]);
   	assert (bufferLen2 == 5);
   	assert (memcmp(buf2, (UCS2[]){GREEK_SMALL_LETTER_ALPHA, COMBINING_MACRON,COMBINING_SMOOTH_BREATHING,COMBINING_ACUTE,COMBINING_IOTA_SUBSCRIPT}, 5*sizeof(UCS2) ) == 0);

   	buf[0] = GREEK_SMALL_LETTER_BETA;
   	buf[1] = PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_MACRON;
   	buf[2] = COMBINING_IOTA_SUBSCRIPT;
   	buf[3] = GREEK_SMALL_LETTER_GAMMA;
   	len = 4;
   	bufferLen2 = 0;
   	bufferLen2 = convertString((UCS2*)buf, len, (UCS2*)buf2, bufferCapacity, COMBINING_ONLY_MODE);
   	//printf("len: %d, %02X %02X\n", bufferLen2, buf2[0], buf2[1]);
   	assert (bufferLen2 == 7);
   	assert (memcmp(buf2, (UCS2[]){GREEK_SMALL_LETTER_BETA,GREEK_SMALL_LETTER_ALPHA, COMBINING_MACRON,COMBINING_SMOOTH_BREATHING,COMBINING_ACUTE,COMBINING_IOTA_SUBSCRIPT,GREEK_SMALL_LETTER_GAMMA}, 7*sizeof(UCS2) ) == 0);





 	UCS2 s1[] = {GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_ALPHA, COMBINING_IOTA_SUBSCRIPT};
 	assert(stripDiacritics(s1, 3, 0) == 2);
 	assert (memcmp(s1, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,GREEK_SMALL_LETTER_ALPHA}, 2 * sizeof(UCS2)) == 0);

 	UCS2 s2[] = {GREEK_SMALL_LETTER_ALPHA, COMBINING_IOTA_SUBSCRIPT};
 	assert(stripDiacritics(s2, 2, 0) == 1);
 	assert (memcmp(s2, (UCS2[]){GREEK_SMALL_LETTER_ALPHA}, 1 * sizeof(UCS2)) == 0);

 	//strip diacritics removing non-greek
 	UCS2 s3[] = {GREEK_SMALL_LETTER_ALPHA, COMBINING_IOTA_SUBSCRIPT, 0x0061};
 	assert(stripDiacritics(s3, 2, 1) == 1);
 	assert (memcmp(s3, (UCS2[]){GREEK_SMALL_LETTER_ALPHA}, 1 * sizeof(UCS2)) == 0);

 	//strip diacritics keeping non-greek
 	UCS2 s4[] = {GREEK_SMALL_LETTER_ALPHA, COMBINING_IOTA_SUBSCRIPT, 0x0061};
 	assert(stripDiacritics(s4, 3, 0) == 2);
 	assert (memcmp(s4, (UCS2[]){GREEK_SMALL_LETTER_ALPHA, 0x0061}, 2 * sizeof(UCS2)) == 0);


	/*
    
    bool l = makeLetter((UCS2*)&buf, &len, 0x03B1, _ACUTE, PRECOMPOSED_WITH_PUA_MODE);
    printf("letter %04x %d, %d\n", buf[0], len, l);

    buf[0] = 0x03B1;
    int x = accentSyllable2((UCS2*)&buf, 1, ACUTE, true, PRECOMPOSED_WITH_PUA_MODE);
	printf("letter2: %04x %d\n", buf[0], x);
*/
   	buf[0] = GREEK_SMALL_LETTER_EPSILON;
   	buf[1] = GREEK_SMALL_LETTER_DIGAMMA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == -1 );

   	buf[0] = GREEK_SMALL_LETTER_DIGAMMA;
   	buf[1] = GREEK_SMALL_LETTER_ZETA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == -1 );


   	buf[0] = GREEK_SMALL_LETTER_PI;
   	buf[1] = GREEK_SMALL_LETTER_SAN;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == -1 );

   	buf[0] = GREEK_SMALL_LETTER_SAN;
   	buf[1] = GREEK_SMALL_LETTER_KOPPA;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == -1 );

   	buf[0] = GREEK_SMALL_LETTER_KOPPA;
   	buf[1] = GREEK_SMALL_LETTER_RHO;
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_INSENSITIVE) == -1 );


	    
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
   	assert( compare((UCS2*)&buf[0], 1, (UCS2*)&buf[1], 1, _HK_COMP_DIA_SENSITIVE) == -1);

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
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_DIA_SENSITIVE) == -1);

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
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 5, _HK_COMP_DIA_SENSITIVE) == -1);

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
   	assert( compare((UCS2*)&buf[0], 3, (UCS2*)&buf[3], 2, _HK_COMP_DIA_SENSITIVE) == -1);

   	//non-greek greater than basic greek range.
   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = 0x0400;

   	buf[2] = GREEK_SMALL_LETTER_ALPHA;
   	buf[3] = 0x0400;
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_DIA_SENSITIVE) == 0);

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
   	assert( compare((UCS2*)&buf[0], 2, (UCS2*)&buf[2], 2, _HK_COMP_INSENSITIVE) == 0 );

   	assert( compareUTF8("α", "αβ", _HK_COMP_DIA_SENSITIVE) == -1);
   	assert( compareUTF8("β", "α", _HK_COMP_DIA_SENSITIVE) == 1);
   	assert( compareUTF8("αβ", "α", _HK_COMP_DIA_SENSITIVE) == 1);
   	assert( compareUTF8("α", "αβ", _HK_COMP_DIA_SENSITIVE) == -1);
   	assert( compareUTF8("ω", "ὤ", _HK_COMP_DIA_SENSITIVE) == -1);
   	assert( compareUTF8("ω", "ὤ", _HK_COMP_INSENSITIVE) == 0);

   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	len = 1;
   	accentSyllable((UCS2*)buf, &len, ACUTE, true, PRECOMPOSED_WITH_PUA_MODE);
   	assert (len == 1);
   	assert (memcmp(buf, (UCS2[]){GREEK_SMALL_LETTER_ALPHA_WITH_VARIA}, 1 * sizeof(UCS2)) != 0);

   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	len = 1;
   	accentSyllable((UCS2*)buf, &len, ACUTE, true, PRECOMPOSED_WITH_PUA_MODE);
   	assert (len == 1);
   	assert (memcmp(buf, (UCS2[]){GREEK_SMALL_LETTER_ALPHA_WITH_TONOS}, 1 * sizeof(UCS2)) == 0);


   	buf[0] = PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_MACRON;
   	buf[1] = COMBINING_IOTA_SUBSCRIPT;
   	len = 2;
   	accentSyllable((UCS2*)buf, &len, GRAVE, true, PRECOMPOSED_WITH_PUA_MODE);
   	assert (len == 2);
   	assert (memcmp(buf, (UCS2[]){PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_VARIA_AND_MACRON, COMBINING_IOTA_SUBSCRIPT}, 2*sizeof(UCS2)) == 0);

   	buf[0] = PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_MACRON;
   	buf[1] = COMBINING_IOTA_SUBSCRIPT;
   	len = 2;
   	accentSyllable((UCS2*)buf, &len, IOTA_SUBSCRIPT, true, PRECOMPOSED_WITH_PUA_MODE);
   	assert (len == 1);
   	assert (memcmp(buf, (UCS2[]){PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_MACRON}, 1 * sizeof(UCS2)) == 0);

   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_MACRON;
   	buf[2] = COMBINING_SMOOTH_BREATHING;
   	buf[3] = COMBINING_ACUTE;
   	buf[4] = COMBINING_IOTA_SUBSCRIPT;
   	len = 5;
   	accentSyllable((UCS2*)buf, &len, GRAVE, true, COMBINING_ONLY_MODE);
   	assert (len == 5);
   	assert (memcmp(buf, (UCS2[]){GREEK_SMALL_LETTER_ALPHA,COMBINING_MACRON,COMBINING_SMOOTH_BREATHING,COMBINING_GRAVE,COMBINING_IOTA_SUBSCRIPT}, 5 * sizeof(UCS2)) == 0);

   	buf[0] = GREEK_SMALL_LETTER_ALPHA;
   	buf[1] = COMBINING_MACRON;
   	buf[2] = COMBINING_SMOOTH_BREATHING;
   	buf[3] = COMBINING_ACUTE;
   	buf[4] = COMBINING_IOTA_SUBSCRIPT;
   	len = 5;
   	accentSyllable((UCS2*)buf, &len, GRAVE, true, PRECOMPOSED_WITH_PUA_MODE);
   	assert (len == 2);
   	assert (memcmp(buf, (UCS2[]){PUA_GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_VARIA_AND_MACRON,COMBINING_IOTA_SUBSCRIPT}, 2 * sizeof(UCS2)) == 0);

/*
   	#define INSENSITIVE ~(_MACRON|_SMOOTH|_ROUGH|_ACUTE|_GRAVE|_CIRCUMFLEX|_IOTA_SUB|_DIAERESIS|_BREVE|_UNDERDOT)
	#define ACCENT_INSENSITIVE ~(_ACUTE|_GRAVE|_CIRCUMFLEX)

   	unsigned int insensitiveMask = ACCENT_INSENSITIVE;// ~(_SMOOTH | _CIRCUMFLEX);
   	int a1 = _CIRCUMFLEX;
   	int a2 = _ACUTE;
   	int a = (a1 & insensitiveMask) == (a2 & insensitiveMask);
   	printf("bool %d\n", a);
*/
   	/*
   	for (int u = 0; u < NUM_UNICODE_MODES; u++)
   	{
	   	for (int i = 0; i < NUM_ACCENTABLE_CHARS; i++)
	   	{
	   		for (int d = 0; d < NUM_DIACRITIC_PERMUTATIONS; d++)
	   		{
	   			accentSyllable();
	   		}
	   	}
	}
   */


   	printf("All tests passed\n");
}
