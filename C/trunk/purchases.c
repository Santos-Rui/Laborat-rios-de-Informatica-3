#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_array.h"
#include "trie.h"
#include "purchases.h"
#define MAXMONTH 12
#define MAXSTR 32
#define MONTHOFFSET(m) m-1
int tot = 0;
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
    char prodKey[MAXSTR];
    int total_bought_by_client;

} PRODUCT_PURCHASES , *PRODUCT_PURCHASE_T;

typedef struct CLIENT_PURCHASES
{

    int client_month_total[MAXMONTH];
    TRIE_T product_list;
    int total_client_bought;
    char clientKey[MAXSTR];
} CLIENT_PURCHASES , *CLIENT_PURCHASE_T;

typedef struct queriestruct{
    int mes;
    char key[MAXSTR];
    STRING_ARRAY_T lista;
}queriestruct;

static PRODUCT_PURCHASE_T PRODUCT_PURCHASES_init()
{   int i;
    PRODUCT_PURCHASE_T ppurch = ( PRODUCT_PURCHASE_T ) malloc ( sizeof ( PRODUCT_PURCHASES ) );

    for ( i=0; i< MAXMONTH; i++ )
    {   ppurch->quantity_normal_mode[i] = 0; 
	ppurch->quantity_promo_mode[i] = 0;
    }

    ppurch->total_bought_by_client = 0;
    return ppurch;
}

static PRODUCT_PURCHASE_T PRODUCT_PURCHASES_update ( PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase, int quantity )
{   
	
	 /*   tot+=quantity;
    printf("%d\n", tot);*/
	switch ( type_purchase )
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

static PRODUCT_PURCHASE_T PRODUCT_PURCHASES_create ( PClientKey key,  char type_purchase, int month, int quantity )
{   PRODUCT_PURCHASE_T product_purchases = PRODUCT_PURCHASES_init();
    strcpy ( product_purchases->clientKey, key );

	    /*tot+=quantity;*/
    /*printf("%d\n", tot);*/
    switch ( type_purchase )
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

/************************************************************************************/

static CLIENT_PURCHASE_T CLIENT_PURCHASES_init()
{   int i;
    CLIENT_PURCHASE_T cpurch = ( CLIENT_PURCHASE_T ) malloc ( sizeof ( CLIENT_PURCHASES ) );

    for ( i=0; i< MAXMONTH; i++ )
    {   cpurch->client_month_total[i]=0;
    }

    cpurch->product_list = TRIE_init();
    cpurch->total_client_bought = 0;
    return cpurch;
}



PURCHASES_T PURCHASES_init()
{   int i;
    PURCHASES *purch = ( PURCHASES * ) malloc ( sizeof ( PURCHASES ) );

    for ( i=0; i < MAXMONTH ; i++ )
    {   purch->month_total[i]=0;
    }

    purch->total_clients=0;
    purch->client_list = TRIE_init();
    return ( ( PURCHASES_T ) purch );
}


PURCHASES_T PURCHASES_insertClient ( PURCHASES_T purchases, PClientKey key )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    CLIENT_PURCHASE_T client_purchases = CLIENT_PURCHASES_init();
    purch->client_list =TRIE_insert ( purch->client_list, key, client_purchases );
    return ( ( PURCHASES_T ) purch );
}

void insertProduct ( NODO_T nodo, void *key )
{   Info info;
    PProductKey pkey= ( PProductKey ) key;
    CLIENT_PURCHASE_T cpurch;
    TRIE_T ptrie;
    printf ( "%s\n", pkey );

    if ( nodo==NULL ) return;

    info = TRIE_getNodeInfo ( nodo );
    cpurch = ( CLIENT_PURCHASE_T ) info;
    ptrie = cpurch->product_list;
    printf ( "%s\n", pkey );
    TRIE_insert ( ptrie, pkey, NULL );
}



PURCHASES_T PURCHASES_insertClientProducts ( PURCHASES_T purchases, PProductKey pkey )
{   CLIENT_PURCHASE_T c_purch=NULL;
    NODO_T nodo;
    TRIE_T c_trie;
    Info info;
    PURCHASES *purch = ( PURCHASES * ) purchases;
    c_trie = purch->client_list;
    nodo = TRIE_search ( c_trie, pkey );
    printf ( "%p\n", nodo );
    TRIE_map ( c_trie, insertProduct, pkey );
    return purchases;
}

PURCHASES_T PURCHASES_insertClientProduct ( PURCHASES_T purchases, PClientKey ckey, PProductKey pkey )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    CLIENT_PURCHASE_T c_purch=NULL;
    PRODUCT_PURCHASE_T ppurch=NULL;
    Info info;
    int i, total = 0;
    NODO_T cnodo, pnodo;
    TRIE_T c_trie;
    c_trie = purch->client_list;
    cnodo = TRIE_search ( c_trie, ckey );
    c_purch = ( CLIENT_PURCHASE_T ) TRIE_getNodeInfo ( cnodo );

    if ( c_purch)
    {   /*c_purch = CLIENT_PURCHASES_init();*/
        /*c_purch->product_list =TRIE_insert ( c_purch->product_list, pkey, NULL );*/
        pnodo = TRIE_search ( c_purch->product_list, pkey );

        if ( pnodo )
        {   ppurch = ( PRODUCT_PURCHASE_T ) TRIE_getNodeInfo ( pnodo );
            strcpy(ppurch->prodKey,(char*)pkey);
            strcpy(ppurch->clientKey,(char*)ckey);

            for ( i=0; i< MAXMONTH; i++ )
            {   /*tot+= ( ppurch->quantity_promo_mode[i]);*/


            }
     
	    /*tot+=total;*/
    /*printf("%d\n", tot);*/
        }
    }



    return ( ( PURCHASES_T ) purch );
}


PURCHASES_T PURCHASES_insertWith ( PURCHASES_T purchases, PClientKey ckey, PProductKey pkey, int month, char type_purchase, int quantity  )
{   PURCHASES *purch = ( PURCHASES * ) purchases;
    CLIENT_PURCHASE_T c_purch=NULL;
    TRIE_T c_trie, p_trie;
    Info info;
    int i;
    PRODUCT_PURCHASE_T product_purchases;
    NODO_T cnodo=NULL, pnodo=NULL;
    c_trie = purch->client_list;
    cnodo = TRIE_search ( c_trie, ckey );


    if ( cnodo )
    {   info =TRIE_getNodeInfo ( cnodo );

        if ( info )
        {   c_purch = ( CLIENT_PURCHASE_T ) info;
            c_purch->client_month_total[MONTHOFFSET ( month )]+=quantity;
            strcpy(c_purch->clientKey,(char*)ckey);
            p_trie = c_purch->product_list;
            pnodo =  TRIE_search ( p_trie, pkey );

            if ( pnodo )
            {   info = TRIE_getNodeInfo ( pnodo );

                /*printf ( "%s %d %c %d\n", pkey, month, type_purchase, quantity );*/

                if ( info )
                {   product_purchases = ( PRODUCT_PURCHASE_T ) info;
                  
                   /* product_purchases = PRODUCT_PURCHASES_update ( product_purchases, month, type_purchase, quantity );*/
                }
            }

            else
            {   product_purchases =PRODUCT_PURCHASES_create ( ckey, type_purchase, month, quantity );
                /*printf ( "%s %d %c %d", pkey, month, type_purchase, quantity );*/
                p_trie =TRIE_insert ( p_trie, pkey,  product_purchases );
            }


            for ( i=0; i< MAXMONTH; i++ )
            {   tot+= ( product_purchases->quantity_promo_mode[i] );
		tot+=( product_purchases->quantity_normal_mode[i] );
            }

            /*tot+=quantity;*/
            /*printf ( "%d\n", tot );*/
        }
    }


    else return NULL;

    return ( ( PURCHASES_T ) purch );
}




int PURCHASES_exists_client ( PURCHASES_T purchases, PClientKey key )
{   NODO_T node;
    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr = purch->client_list;
    node = TRIE_search ( ( TRIE_T ) tr, key );
    return ( node!=NULL );
}


int PURCHASES_exists_clientProduct ( PURCHASES_T purchases, PClientKey ckey , PProductKey pkey )
{   NODO_T node;
    Info info;
    PURCHASES *purch = ( PURCHASES * ) purchases;
    CLIENT_PURCHASE_T cpurch;
    TRIE_T tr1, tr2;
    tr1= purch->client_list;
    node = TRIE_search ( ( TRIE_T ) tr1, ckey );

    if ( node )
    {   cpurch = ( CLIENT_PURCHASE_T ) TRIE_getNodeInfo ( node );
        tr2 = cpurch->product_list;
        node = NULL;
        node = TRIE_search ( ( TRIE_T ) tr2, pkey );
        return ( node!=NULL );
    }

    return 0;
}

void PURCHASES_delete_client ( PURCHASES_T purchases, PClientKey key )
{   /*XXX Apagar total em fich_cliente e obter total em fich_prod*/
    NODO_T node;
    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr = purch->client_list;
    TRIE_delete ( tr, key );
}

void PURCHASES_delete_clientProduct ( PURCHASES_T purchases, PClientKey ckey, PProductKey pkey )
{   /*XXX Apagar total em fich_cliente e obter total em fich_prod*/
    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr1, tr2;
    NODO_T nodo;
    CLIENT_PURCHASE_T cpurch;
    tr1 = purch->client_list;
    nodo = TRIE_search ( ( TRIE_T ) tr1, ckey );

    if ( nodo )
    {
        {   cpurch = ( CLIENT_PURCHASE_T ) TRIE_getNodeInfo ( nodo );
            tr2 = cpurch->product_list;
            TRIE_delete ( tr2, pkey );
        }
    }
}
void PURCHASES_destroy ( PURCHASES_T purchases ) /*pus em coment para tirar warnings*/
{   /*PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T tr1, tr2;
    NODO_T nodo;
    CLIENT_PURCHASE_T cpurch;
    tr1 = purch->client_list;*/
}
    /*traverse all clients deleting all trie*/
    /* cpurch = (CLIENT_PURCHASE_T)getNodeInfo(nodo);
     tr2 = cpurch->product_list;
     delete_t ( tr2, pkey );

    }
    PURCHASES *purch = ( PURCHASES * ) purchases;
    trie_free ( purch->product_list );*/

/*QUERIE 8*/




STRING_ARRAY_T PURCHASES_getProductClientList ( PURCHASES_T purchases, PProductKey key){
    /* Correr clientes todos , ver se tem produto, se tiver guardar a chave no string array N E P

    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T trieClientes = purch->client_list;
    STRING_ARRAY_T lista=STRING_ARRAY_init();
    TRIE_map ( trieClientes, checkIfBoughtX, (void*)lista);*/
    return NULL;
}

/*QUERIE 9*/

void checkIfBoughtInMonthX (NODO_T nodo, void* aux){

    char* codigo;
    char* quantidade;
    queriestruct* estrutura = (queriestruct*) aux;

    PRODUCT_PURCHASE_T fichaP = ( PRODUCT_PURCHASE_T ) ( TRIE_getNodeInfo ( nodo ) );

    if ( fichaP ) {
        if (fichaP->total_bought_by_client!=0){/*
            strcpy(codigo,estrutura->key);
            quantidade = sprintf(quantidade, "%d", fichaP->quantity_normal_mode[estrutura->mes] + fichaP->quantity_promo_mode[estrutura->mes]);
            strcat (codigo,quantidade);*/
            STRING_ARRAY_insert(estrutura->lista,fichaP->prodKey);
        }
    }
}

STRING_ARRAY_T PURCHASES_getClientMostBoughtProductListByMonthDesc ( PURCHASES_T purchases, PClientKey ckey, Month mes){

    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T TrieClientes = purch->client_list;

    TRIE_T TrieProdutos;
    NODO_T NodoCliente;
    queriestruct * aux;
    CLIENT_PURCHASES* clientpurch;
    CLIENT_PURCHASE_T FichaCliente;
    
    aux=(queriestruct*)malloc(sizeof(struct queriestruct));
    aux->mes = mes;
    strcpy(aux->key,(char*)ckey);
    aux->lista=STRING_ARRAY_init();
    printf("%p  %p\n", aux->key, ckey);
    getchar();
    getchar();
     
    NodoCliente = TRIE_search(TrieClientes,ckey);
    FichaCliente = ( CLIENT_PURCHASE_T ) ( TRIE_getNodeInfo ( NodoCliente ) );
    clientpurch = (CLIENT_PURCHASES*) FichaCliente;
    TrieProdutos = clientpurch->product_list;

    TRIE_map ( TrieProdutos, checkIfBoughtInMonthX, (void*)aux);
    
    return aux->lista;

}




 /*QUERIE 10*/
 void check12months ( NODO_T nodo, void* lista )
{
    int i=0;
    int control=1;
    STRING_ARRAY_T list=(STRING_ARRAY_T) lista;
    CLIENT_PURCHASE_T fichaC = ( CLIENT_PURCHASE_T ) ( TRIE_getNodeInfo ( nodo ) );
    if ( fichaC )
    {   
        for(i=0; i<12 && control==1 ;i++){
            if (fichaC -> client_month_total[i]==0) {control=0;}
        }
    }
    if (control==1)
        STRING_ARRAY_insert(list,fichaC ->clientKey);
}



STRING_ARRAY_T PURCHASES_getClientListAllMonth ( PURCHASES_T purchases)
{
    STRING_ARRAY_T lista=STRING_ARRAY_init();
    PURCHASES *purch = ( PURCHASES * ) purchases;
    TRIE_T trieClientes = purch->client_list;
    TRIE_map ( trieClientes, check12months, (void*)lista );
    return lista;
}

/*
 querie 11
void getTotalClientsAndPurshasesList ( PURCHASES_T, int total_purshases_by_month[], int total_clients_by_month[] );


 querie 12
char **getNthMostSoldProductList ( PURCHASES_T, AllocatedSize * );

querie 13

char **get_client_3MostBoughtProducts ( PURCHASES_T, int * )

querie 14

int getTotalClientsWithNoPurchases ( PURCHASES_T );

int getTotalProductsNotBought ( PURCHASES_T );

*/



