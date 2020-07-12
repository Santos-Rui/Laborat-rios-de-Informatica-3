#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "abin.h"
#include "purchases.h"
#define MAXMONTH 16
#define MAXSTR 32
#define MONTHOFFSET(m) m-1



static int contador;

typedef struct PURCHASES
{

    int month_total[MAXMONTH];
    TRIE_T client_list;
    int total_clients;

} PURCHASES;
typedef struct PRODUCT_PURCHASES
{   int quantity_normal_mode[MAXMONTH];
    int quantity_promo_mode[MAXMONTH];
    char clientKey[MAXSTR];
    char productKey[MAXSTR];
    int total_bought_by_client;

} PRODUCT_PURCHASES , *PRODUCT_PURCHASE_T;

typedef struct CLIENT_PURCHASES
{

    int client_month_total[MAXMONTH];
    ABin_T product_list;
    int total_client_bought;
    char clientKey[MAXSTR];
} CLIENT_PURCHASES , *CLIENT_PURCHASE_T;

typedef struct client_product{


    char clientKey[MAXSTR];
    char productKey[MAXSTR];

}* ClientProduct;

static PRODUCT_PURCHASE_T PRODUCT_PURCHASES_init()
{   int i;
    PRODUCT_PURCHASE_T ppurch = ( PRODUCT_PURCHASE_T ) malloc ( sizeof ( PRODUCT_PURCHASES ) );

    for ( i=0; i< MAXMONTH; i++ )
    {   ppurch->quantity_normal_mode[i] = ppurch->quantity_promo_mode[i] = 0;
    }

    ppurch->total_bought_by_client = 0;
    return ppurch;
}

int compare_items ( const void *pvItem1, const void *pvItem2 , void *c )
{   PRODUCT_PURCHASE_T p1, p2;
    p1 = (PRODUCT_PURCHASE_T)pvItem1;
    p2 = (PRODUCT_PURCHASE_T) pvItem2;
    /* Ordena pelo nome da "variável" */
    return strcmp ( p1->productKey, p2->productKey );
}
static PRODUCT_PURCHASE_T PRODUCT_PURCHASES_update ( PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase, int quantity )
{   switch ( type_purchase )
    {   case 'N':
            product_purchases->quantity_normal_mode[MONTHOFFSET ( month )]+=quantity;
            break;

        case 'P':
            product_purchases->quantity_promo_mode[MONTHOFFSET ( month )]+=quantity;
            break;
    }

    product_purchases->total_bought_by_client+=quantity;
    return product_purchases;
}

static PRODUCT_PURCHASE_T PRODUCT_PURCHASES_create ( PClientKey ckey, PProductKey pkey,  char type_purchase, int month, int quantity )
{   PRODUCT_PURCHASE_T product_purchases = PRODUCT_PURCHASES_init();
    strcpy ( product_purchases->clientKey, ckey );
    strcpy ( product_purchases->productKey, pkey );
    /*switch ( type_purchase )
    {   case 'N':
            product_purchases->quantity_normal_mode[MONTHOFFSET ( month )]=quantity;
            break;

        case 'P':
            product_purchases->quantity_promo_mode[MONTHOFFSET ( month )]=quantity;
            break;
    }

    product_purchases->total_bought_by_client+=quantity;*/
    return product_purchases;
}

/************************************************************************************/

static CLIENT_PURCHASE_T CLIENT_PURCHASES_init()
{   int i;
    void * arg;
    CLIENT_PURCHASE_T cpurch = ( CLIENT_PURCHASE_T ) malloc ( sizeof ( CLIENT_PURCHASES ) );

    for ( i=0; i< MAXMONTH; i++ )
    {   cpurch->client_month_total[i]=0;
    }

    cpurch->product_list = ABin_init(compare_items, arg);
    cpurch->total_client_bought = 0;
    return cpurch;
}

TRIE_T getList ( PURCHASES_T purchases )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr;
    tr = purch->client_list;
    return tr;
}





PURCHASES_T PURCHASES_init()
{   int i;
    PURCHASES *purch = ( PURCHASES * ) malloc ( sizeof ( PURCHASES ) );

    for ( i=0; i < MAXMONTH ; i++ )
    {   purch->month_total[i]=0;
    }

    purch->client_list = TRIE_init();
    purch->total_clients=0;
    return ( ( PURCHASES_T ) purch );
}


PURCHASES_T PURCHASES_insertClient ( PURCHASES_T purchases, PClientKey key )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr;
    CLIENT_PURCHASE_T client_purchases = CLIENT_PURCHASES_init();
    tr = purch->client_list;
    tr=TRIE_insert ( tr, key, client_purchases );
    return ( ( PURCHASES_T ) purch );
}

void insertProduct ( NODO_T nodo , void *key )
{   PProductKey pKey = (PProductKey) key;
    CLIENT_PURCHASE_T cpurch;
    PRODUCT_PURCHASE_T ppurch;
    ABin_T tree;
    Info info;

    if ( nodo==NULL ) return;

    info = TRIE_getNodeInfo ( nodo );
    cpurch = ( CLIENT_PURCHASE_T ) info;
    tree = cpurch->product_list;
    /*  printf ( "%d\n", getFolhaControl ( nodo ) );*/
    ppurch = PRODUCT_PURCHASES_create(cpurch->clientKey, pKey, 0, 0 ,0);
    ppurch = ABin_insert(tree, ppurch);
    /*TRIE_insert ( ptrie, pkey, NULL );*/
}



PURCHASES_T PURCHASES_insertClientProducts ( PURCHASES_T purchases, PProductKey pkey )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T c_trie;
    c_trie = purch->client_list;


    TRIE_map ( c_trie, &insertProduct, pkey);
    return ( PURCHASES_T ) purch;
}

/*PURCHASES_T PURCHASES_insertClientProduct ( PURCHASES_T purchases, PClientKey ckey, PProductKey pkey )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    CLIENT_PURCHASE_T c_purch=NULL;
    PRODUCT_PURCHASES * ppurch;
    TRIE_T c_trie;
    c_trie = purch->client_list;

    if ( TRIE_search ( c_trie, ckey ) )
    {   c_purch = CLIENT_PURCHASES_init();
      ppurch = PRODUCT_PURCHASES_init();
      ppurch = PRODUCT_PURCHASES_create(ckey, pkey, 0,0,0);
      c_purch->product_list =ABin_insert(c_purch->product_list, ppurch)
    }

    return ( ( PURCHASES_T ) purch );
}*/


/*PURCHASES_T PURCHASES_insertWith ( PURCHASES_T purchases,PClientKey ckey, PProductKey pkey, int month, char type_purchase, int quantity  )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    CLIENT_PURCHASE_T c_purch=NULL;
    TRIE_T c_trie, p_trie;
    PRODUCT_PURCHASE_T product_purchases;
    NODO_T cnodo=NULL, pnodo=NULL;
    Info info;
    c_trie = purch->client_list;
    cnodo = TRIE_search ( c_trie, ckey );

    if ( cnodo )
    {   info =TRIE_getNodeInfo ( cnodo );

        if ( info )
        {   c_purch = ( CLIENT_PURCHASE_T ) info;
            c_purch->client_month_total[MONTHOFFSET ( month )]+=quantity;
            p_trie = c_purch->product_list;
            pnodo = TRIE_search ( p_trie, pkey );

            if ( pnodo )
            {   info = TRIE_getNodeInfo ( pnodo );

                if ( info )
                {   product_purchases = ( PRODUCT_PURCHASE_T ) info;
                    product_purchases = PRODUCT_PURCHASES_update ( product_purchases, month, type_purchase, quantity );
                }

                else
                {   product_purchases =PRODUCT_PURCHASES_create ( ckey, type_purchase, month, quantity );
                }

                p_trie =TRIE_insert ( p_trie, pkey,  product_purchases );
            }
        }
    }

    else return NULL;

    return ( ( PURCHASES_T ) purch );
}


int PURCHASES_exists_client ( PURCHASES_T purchases, PClientKey key )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr = purch->client_list;
    return ( TRIE_search ( ( TRIE_T ) tr, key ) !=NULL );
}


int PURCHASES_exists_clientProduct ( PURCHASES_T purchases, PClientKey ckey , PProductKey pkey )
{   NODO_T node;
    PURCHASES *purch = ( PURCHASES * ) purchases;
    CLIENT_PURCHASE_T cpurch;
    TRIE_T tr1, tr2;
    tr1= purch->client_list;
    node = TRIE_search ( ( TRIE_T ) tr1, ckey );

    if ( node )
    {   cpurch = ( CLIENT_PURCHASE_T ) TRIE_getNodeInfo ( node );
        tr2 = cpurch->product_list;
        return ( TRIE_search ( tr2, pkey ) !=0 );
    }

    return 0;
}
*/
void PURCHASES_delete_client ( PURCHASES_T purchases, PClientKey key )
{   /*XXX Apagar total em fich_cliente e obter total em fich_prod*/
    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr = purch->client_list;
    TRIE_delete ( tr, key );
}

/*void PURCHASES_delete_clientProduct ( PURCHASES_T purchases, PClientKey ckey, PProductKey pkey )
{ */  /*XXX Apagar total em fich_cliente e obter total em fich_prod*/
   /* PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr1, tr2;
    NODO_T nodo;
    CLIENT_PURCHASE_T cpurch;
    tr1 = purch->client_list;
    nodo = TRIE_search ( tr1, ckey );

    if ( nodo )
    {   cpurch = ( CLIENT_PURCHASE_T ) TRIE_getNodeInfo ( nodo );
        tr2 = cpurch->product_list;
        TRIE_delete ( tr2, pkey );
    }

    return;
}*/
/*void PURCHASES_destroy ( PURCHASES_T purchases )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr1, tr2;
    NODO_T nodo;
    CLIENT_PURCHASE_T cpurch;
    tr1 = purch->client_list;
*/
/*traverse all clients deleting all trie*/
/* cpurch = (CLIENT_PURCHASE_T)getNodeInfo(nodo);
 tr2 = cpurch->product_list;
 delete_t ( tr2, pkey );

}
PURCHASES *purch = ( PURCHASES * ) purchases;
trie_free ( purch->product_list );*/
/*}*/

/* querie 8 */
/*char **PURCHASES_getProductClientList ( PURCHASES_T , PProductKey, PAllocatedSize * );
*/

/* querie 9 */
/*char **PURCHASES_getClientMostBoughtProductListByMonthDesc ( PURCHASES_T , PProductKey , int );
*/

/* querie 10 */
void check12months ( NODO_T nodo, void*arg )
{
	char ** list = (char**) arg;
	CLIENT_PURCHASE_T fichaC = ( CLIENT_PURCHASE_T ) ( TRIE_getNodeInfo ( nodo ) );

    if ( fichaC )
    {   contador++;
        list = realloc ( list,sizeof ( char * ) *contador ); /*aumento o tamanho do array de arrays*/
        list[contador-1] = ( char * ) malloc ( sizeof ( char * ) *MAXSTR ); /*alocar o array///MAXSTR OU 6/7*/
        strcpy ( list[contador],fichaC->clientKey );
    }
}



/*char **PURCHASES_getClientListAllMonth ( PURCHASES_T purchases, PAllocatedSize *size )
{
    char **list=NULL;
    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T trieClientes = purch->client_list;
    contador=0;
    TRIE_map ( trieClientes, check12months, list );*//*correr a lista e sacas or nomes dos que comprar nos 12 para o list*/
   /* *size=contador;
    return list;
}
*/

/* querie 11 */
/*void getTotalClientsAndPurshasesList ( PURCHASES_T, int total_purshases_by_month[], int total_clients_by_month[] );
*/

/* querie 12 */
/*char **getNthMostSoldProductList ( PURCHASES_T, AllocatedSize * );
*/
/*querie 13 */

/*char **get_client_3MostBoughtProducts ( PURCHASES_T, int * )
*/
/*querie 14 */
/*
int getTotalClientsWithNoPurchases ( PURCHASES_T );

int getTotalProductsNotBought ( PURCHASES_T );
*/










