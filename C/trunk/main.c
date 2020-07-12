#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "client_cat.h"
#include "product_cat.h"
#include "accounting.h"
#include "purchases.h"
#include "trie.h"
#include "interface.c"

void foo_bar ( NODO_T nodo )
{   printf ( "%p\n", ( void * ) nodo );
}


int main ()
{   int linesClient = 0, linesProd=0;
    int validated;
    /*char **navP;
    int resC=0, resP=0;
    int x;
    int qtN, qtP;
    float value;
    char a = 'F';*/
    /*char fichProd[MAXBUFF], fichClient[MAXBUFF], fichCompras[MAX_NAME_SIZE];*/
    STRING_ARRAY_T stray;
    CL_CAT_T cc = CLIENT_CAT_init();
    PR_CAT_T cp = PRODUCT_CAT_init();
    ACCOUNTING_T cont = ACCOUNTING_init();
    PURCHASES_T comp = PURCHASES_init();
    linesProd++;
    linesClient++;
    /*printf ( "Especifique o nome do Ficheiro de CLIENT_CAT incluindo a extensão: " );
    scanf ( "%s", fichClient );
    printf ( "Especifique o nome do Ficheiro de PRODUCT_CAT_ incluindo a extensão: " );
    scanf ( "%s", fichProd );*/
    /*a='F';*/
    linesClient=  readFiles ( NULL, cc, NULL, comp,  FILE_CLIENT, MAXBUFF, "./test/FichClientes.txt", NULL );
    linesProd =  readFiles  ( cp, NULL, cont, comp ,  FILE_PRODUCT, MAXBUFF, "./test/FichProdutos.txt", NULL );
    readFiles ( cp, cc, cont, comp,  FILE_SALES, MAXBUFF, "./test/Compras.txt", &validated );
    printf ( "%s => Clientes inseridos: %d\n", "./test/FichClientes.txt", linesClient );
    printf ( "%s => Produtos inseridos: %d\n", "./test/FichProdutos.txt", linesProd );
    printf ( "%d => Compras validadas\n", validated );
    /*stray=PURCHASES_getClientListAllMonth(comp);
    navigation((char**)STRING_ARRAY_getStringArrayPointer(stray),STRING_ARRAY_getNumElems(stray));*/
    main_menu(cc,cp,cont,comp);
    /* printf ( "%d => \n", ACCOUNTING_totalBilledByMonth ( cont, "CA6211", 9, &qtN, &qtP, &value ) );
     printf ( "%d %d %f => \n", qtN, qtP, value ) ;*/
    /*navC = ACCOUNTING_getNonBilledProducts ( cont, &x );
    printf ( "%d => \n", x );
    navigation ( navC , x );
    x = PRODUCT_CAT_getTotalKeysBeginningWith ( a, cp );
    printf ( "%d\n",x );*/
    /* XXX A decidir se alocação será dentro ou fora das funções*/
    /* navP = malloc_buffered_strings ( x, MAXBUFF );
     resC=CLIENT_CAT_getKeys ( cc, navC );
     PRODUCT_CAT_getKeysPrefix ( cp, navP, a );
     printf ( "%d",x );

     if ( x != 0 )
         navigation ( navP , x );

     navigation ( navC, resC );*/
    CLIENT_CAT_destroy ( cc );
    PRODUCT_CAT_destroy ( cp );
    /* free_buffered_strings ( navP, x );
     free_buffered_strings ( navC, linesClient );*/
    return 0;
}










