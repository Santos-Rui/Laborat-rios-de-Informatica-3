
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_array.h"
#include "trie.h"
#define MAXBUFF 32
int main ()
{   TRIE_T t= TRIE_init();
    STRING_ARRAY_T str = STRING_ARRAY_init();
    FILE *fich;
    Info info = NULL;
    int linha = 0;
    char buffer[MAXBUFF];
    NODO_T *f;
    fich= fopen ( "../test/FichProdutos.txt", "r" );

    /*XXX tirar validated a 0*/
    if ( fich != NULL )
    {   while ( fgets ( buffer, MAXBUFF, fich ) != NULL )
        {   buffer[strlen ( buffer )-2] = '\0';
	    if(linha%2==0)
            t = TRIE_insert ( t , buffer , NULL );
	    else
            t = TRIE_insert ( t , buffer , (void*)1 );
	    linha++;
        }

        fclose ( fich );
    }

    else perror ( "../test/FichProdutos.txt" );

str = TRIE_getAllKeysWithoutInfo(t, str);

// for ( linha = 0; linha < STRING_ARRAY_getNumElems(str); linha++ )
//     printf ( "%s\n", STRING_ARRAY_getStringAtPos ( str, linha ) );
//linha = imprimir_tmp ( t );
printf ( "%d\n", STRING_ARRAY_getNumElems ( str ) );
free ( t );
return 0;
}












