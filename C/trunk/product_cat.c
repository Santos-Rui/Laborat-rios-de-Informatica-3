#include <stdlib.h>
#include "trie.h"
#include "bool.h"
#include "product_cat.h"

typedef struct PR_CAT
{   TRIE_T *lista_clientes;

} PR_CAT;

PR_CAT_T PRODUCT_CAT_init()
{   TRIE_T tr = TRIE_init();
    return ( ( PR_CAT_T ) tr );
}

PR_CAT_T PRODUCT_CAT_insert ( PR_CAT_T catalogo, ProdKey Key )
{   TRIE_T t = ( TRIE_T ) catalogo;
    t =TRIE_insert ( t, Key, NULL );
    return ( ( PR_CAT_T ) t );
}

int PRODUCT_CAT_search ( PR_CAT_T catalogo, ProdKey Key )
{   Boolean exists = true;

    if ( !TRIE_search ( ( TRIE_T ) catalogo, Key ) )
        exists=false;

    return exists;
}

void PRODUCT_CAT_delete ( PR_CAT_T catalogo, ProdKey Key )
{   TRIE_delete ( ( TRIE_T ) catalogo, Key );
}
void PRODUCT_CAT_destroy ( PR_CAT_T catalogo )
{   TRIE_destroy ( ( TRIE_T ) catalogo );
    return;
}
void PRODUCT_CAT_getLetters ( PR_CAT_T catalogo, int v[] )
{   TRIE_T t = ( TRIE_T ) catalogo;
    TRIE_getLetters ( t,v );
}
STRING_ARRAY_T PRODUCT_CAT_getKeys ( PR_CAT_T catalogo )
{   TRIE_T t = ( TRIE_T ) catalogo;
    STRING_ARRAY_T buff = STRING_ARRAY_init();
    return TRIE_getAllKeys ( t, buff );
}

int PRODUCT_CAT_getTotalKeysBeginningWith ( char a, PR_CAT_T catalogo )
{   return TRIE_getTotalKeysBeginningWith ( a, ( TRIE_T ) catalogo, 'A' );
}

STRING_ARRAY_T PRODUCT_CAT_getKeysBegginingWithChar ( PR_CAT_T catalogo, char first )
{   TRIE_T t = ( TRIE_T ) catalogo;
    char intern_buff[ARRAY_SIZE];
    STRING_ARRAY_T str = STRING_ARRAY_init();
    int index = 1;
    NODO_T ap = TRIE_getFirtstCharKeyNode ( first, t );
    intern_buff[0]= first;
    return TRIE_getAllKeysFromNode ( ap, str, intern_buff, index );
}

