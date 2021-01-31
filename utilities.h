//
//  utilities.h
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 3/4/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

#ifndef utilities_h
#define utilities_h
#include <stddef.h> //for size_t
#include <stdbool.h>

#ifndef __EMSCRIPTEN__
#include <stdio.h>
#endif

typedef unsigned short UCS2;
//typedef uint16_t UCS2;

bool ucsplice(UCS2 *string, size_t *len, size_t buffer_capacity, size_t offset, size_t replacing, UCS2 *insert, size_t insert_len);

int ucs2_to_utf8 (UCS2 ucs2, unsigned char * utf8);
UCS2 utf8_to_ucs2 (const unsigned char * input, const unsigned char ** end_ptr);

void utf8_to_ucs2_string(const char *utf8, UCS2 *ucs2, size_t *len);
int ucs2_to_utf8_string(UCS2 *ucs2, size_t len, unsigned char *utf8);

#endif /* utilities_h */
