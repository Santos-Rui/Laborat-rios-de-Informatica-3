#ifndef CL_CAT_H
#define CL_CAT_H
#include "string_array.h"
#include "bool.h"
typedef char* ClientKey;
typedef struct CL_CAT * CL_CAT_T;
CL_CAT_T CLIENT_CAT_init();
CL_CAT_T CLIENT_CAT_insert(CL_CAT_T, ClientKey);
Boolean  CLIENT_CAT_search(CL_CAT_T , ClientKey);
void CLIENT_CAT_delete(CL_CAT_T, ClientKey);
void CLIENT_CAT_destroy ( CL_CAT_T);
void CLIENT_CAT_getLetters(CL_CAT_T c, int v []);
int CLIENT_CAT_getTotalKeysBeginningWith ( char, CL_CAT_T );
STRING_ARRAY_T CLIENT_CAT_getKeys(CL_CAT_T);
STRING_ARRAY_T CLIENT_CAT_getKeysBegginingWithChar( CL_CAT_T, char);
#endif 

