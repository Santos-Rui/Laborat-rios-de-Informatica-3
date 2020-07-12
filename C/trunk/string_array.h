#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

#include "bool.h"
typedef struct STRING_ARRAY * STRING_ARRAY_T;


STRING_ARRAY_T STRING_ARRAY_init();

STRING_ARRAY_T STRING_ARRAY_insert(STRING_ARRAY_T, char *);

const char * STRING_ARRAY_getStringAtPos(STRING_ARRAY_T, int);

const char ** STRING_ARRAY_getStringArrayPointer(STRING_ARRAY_T);

int STRING_ARRAY_getNumElems(STRING_ARRAY_T);

int STRING_ARRAY_getSize(STRING_ARRAY_T);
void STRING_ARRAY_destroy(STRING_ARRAY_T);

Boolean STRING_ARRAY_isEmpty(STRING_ARRAY_T);

#endif 
