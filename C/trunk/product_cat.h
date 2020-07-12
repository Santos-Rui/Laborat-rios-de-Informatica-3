
#ifndef PR_CAT_H
#define PR_CAT_H
#include "string_array.h"
#include "bool.h"
typedef char* ProdKey;
typedef struct PR_CAT * PR_CAT_T;


PR_CAT_T PRODUCT_CAT_init();
PR_CAT_T PRODUCT_CAT_insert(PR_CAT_T, ProdKey);
Boolean  PRODUCT_CAT_search(PR_CAT_T , ProdKey );
void PRODUCT_CAT_delete(PR_CAT_T, ProdKey);
void PRODUCT_CAT_destroy ( PR_CAT_T);
void PRODUCT_CAT_getLetters ( PR_CAT_T c, int v[] );
int PRODUCT_CAT_getTotalKeysBeginningWith ( char, PR_CAT_T);
STRING_ARRAY_T PRODUCT_CAT_getKeys(PR_CAT_T);
STRING_ARRAY_T PRODUCT_CAT_getKeysBegginingWithChar( PR_CAT_T, char);

#endif 

