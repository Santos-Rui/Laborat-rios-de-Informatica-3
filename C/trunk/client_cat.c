#include <stdlib.h>
#include "trie.h"
#include "client_cat.h"
#include "bool.h"
#include "string_array.h"
#include <ctype.h>
typedef struct CL_CAT
{   TRIE_T *lista_clientes;

} CL_CAT;

CL_CAT_T CLIENT_CAT_init()
{   TRIE_T tr = TRIE_init();
    return ( ( CL_CAT_T ) tr );
}

CL_CAT_T CLIENT_CAT_insert ( CL_CAT_T catalogo, ClientKey key )
{   TRIE_T t = ( TRIE_T ) catalogo;
    t =TRIE_insert ( t, key, NULL );
    return ( ( CL_CAT_T ) t );
}

Boolean CLIENT_CAT_search ( CL_CAT_T catalogo, ClientKey key )
{   Boolean exists = false;

    if ( TRIE_search ( ( TRIE_T ) catalogo, key ) )
        exists = true;

    return exists;
}

void CLIENT_CAT_delete ( CL_CAT_T catalogo, ClientKey key )
{   TRIE_delete ( ( TRIE_T ) catalogo, key );
}

void CLIENT_CAT_destroy ( CL_CAT_T catalogo )
{   TRIE_destroy ( ( TRIE_T ) catalogo );
}

void CLIENT_CAT_getLetters ( CL_CAT_T catalogo, int v[] )
{   TRIE_T t = ( TRIE_T ) catalogo;
    TRIE_getLetters ( t,v );
}
STRING_ARRAY_T CLIENT_CAT_getKeys ( CL_CAT_T catalogo )
{   TRIE_T t = ( TRIE_T ) catalogo;
    STRING_ARRAY_T str = STRING_ARRAY_init();
    return TRIE_getAllKeys ( t, str );
}
int CLIENT_CAT_getTotalKeysBeginningWith ( char a, CL_CAT_T catalogo )
{   return TRIE_getTotalKeysBeginningWith ( a, ( TRIE_T ) catalogo , 'A' );
}
STRING_ARRAY_T CLIENT_CAT_getKeysBegginingWithChar ( CL_CAT_T catalogo, char first )
{   TRIE_T t = ( TRIE_T ) catalogo;
    char intern_buff[ARRAY_SIZE];
    STRING_ARRAY_T str = STRING_ARRAY_init();
    int index = 1;
    NODO_T ap;

    if ( islower ( first ) )
        first = toupper ( first );

    ap = TRIE_getFirtstCharKeyNode ( first, t );
    intern_buff[0]= first;
    return TRIE_getAllKeysFromNode ( ap, str, intern_buff, index );
}








