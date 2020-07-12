#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bool.h"
#include "trie.h"
#include "product_accounting.h"
#include "accounting.h"
#include "string_array.h"

#define MAXSTR 32
#define MAXMONTH 16
#define MONTHOFFSET(month) (month-1)

typedef struct ACCOUNTING
{

    int month_total_billed[MAXMONTH];
    int month_total_single_purch[MAXMONTH];
    int total_prod_comp_mes[MAXMONTH];
    TRIE_T product_list;
    int total_prod_comp;

} ACCOUNTING;


ACCOUNTING_T ACCOUNTING_init()
{   int i;
    ACCOUNTING *cont = ( ACCOUNTING * ) malloc ( sizeof ( ACCOUNTING ) );
    cont->product_list = TRIE_init();
    cont->total_prod_comp = 0;

    for ( i=0; i < MAXMONTH ; i++ )
    {   cont->month_total_single_purch[i]=0;
        cont->month_total_billed[i]=0;
        cont->total_prod_comp_mes[i]=0;
    }

    return ( ( ACCOUNTING_T ) cont );
}

ACCOUNTING_T ACCOUNTING_insertProductKey ( ACCOUNTING_T accounting, AProductKey key )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting = NULL;
    cont->product_list =TRIE_insert ( cont->product_list, key, single_accounting );
    return ( ( ACCOUNTING_T ) cont );
}



ACCOUNTING_T ACCOUNTING_insertProductAccounting ( ACCOUNTING_T accounting, AProductKey key, AMonth month, AccountType type_accounting, PriceValue value, AQuantity quantity  )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );

    if ( nodo )
    {   if ( TRIE_getNodeInfo ( nodo ) )
        {   single_accounting = PRODUCT_ACCOUNTING_update ( ( PRODUCT_ACCOUNTING_T ) TRIE_getNodeInfo ( nodo ) , month, type_accounting,value,quantity );
        }

        else
        {   single_accounting =PRODUCT_ACCOUNTING_create ( type_accounting, month,  value, quantity );
        }

        cont->total_prod_comp++;
        cont->month_total_billed[MONTHOFFSET ( month )]++;
        cont->month_total_single_purch[MONTHOFFSET ( month )]+=quantity*value;
        cont->total_prod_comp_mes[MONTHOFFSET ( month )]++;
        tr =TRIE_insert ( tr, key, single_accounting );
    }

    return ( ( ACCOUNTING_T ) cont );
}
PRODUCT_ACCOUNTING_T ACCOUNTING_search ( ACCOUNTING_T accounting, AProductKey key )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo = TRIE_search ( tr, key );
    Info info = TRIE_getNodeInfo ( nodo );

    if ( info==NULL ) return NULL;

    return ( PRODUCT_ACCOUNTING_T ) info;
}

int ACCOUNTING_getTotalQuantityByMonthByAnyType ( ACCOUNTING_T accounting, AProductKey key,  AMonth month )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;
            return PRODUCT_ACCOUNTING_getTotalQuantityByMonthByAnyType ( single_accounting, month );
        }

        else
            return 0;
    }

    return 0;
}

int ACCOUNTING_getTotalQuantityInMonthByType ( ACCOUNTING_T accounting, AProductKey key,  AMonth month, AccountType type_accounting )
{   int PRODUCT_ACCOUNTING_getTotalQuantityByMonthByType ( PRODUCT_ACCOUNTING_T pat, int month, char type_accounting );
    ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;
            return PRODUCT_ACCOUNTING_getTotalQuantityByMonthByType ( single_accounting, month, type_accounting );
        }

        else
            return 0;
    }

    return 0;
}

int ACCOUNTING_getTotalQuantityAllYearByType ( ACCOUNTING_T accounting, AProductKey key, AccountType type_accounting )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;
    AQuantity qt = 0;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;

            switch ( type_accounting )
            {   case 'N':
                    qt = PRODUCT_ACCOUNTING_getTotalQuantityAllYearByType ( single_accounting, type_accounting );
                    break;

                case 'P':
                    qt = PRODUCT_ACCOUNTING_getTotalQuantityAllYearByType ( single_accounting, type_accounting );
                    break;
            }

            return qt;
        }

        else
            return 0;
    }

    return 0;
}
int ACCOUNTING_getTotalQuantityAllYearAnyType ( ACCOUNTING_T accounting, AProductKey key )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;
            return PRODUCT_ACCOUNTING_getTotalQuantityAllYearAnyType ( single_accounting );
        }

        else
            return 0;
    }

    return 0;
}


float ACCOUNTING_getTotalBilledByMonthByType ( ACCOUNTING_T accounting, AProductKey key,  AMonth month, AccountType type_accounting )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;
            return PRODUCT_ACCOUNTING_getTotalBilledByMonthByType(single_accounting, month, type_accounting);
        }

        else
            return 0;
    }

    return 0;
}

float ACCOUNTING_getTotalBilledByMonthByAnyType ( ACCOUNTING_T accounting,  AProductKey key , AMonth month )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;
            return PRODUCT_ACCOUNTING_getTotalBilledByMonthByAnyType ( single_accounting, month );
        }

        else
            return 0;
    }

    return 0;
}

float ACCOUNTING_getTotalBilledAllYearByAnyType ( ACCOUNTING_T accounting,  AProductKey key)
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;
            return PRODUCT_ACCOUNTING_getTotalBilledAllYearAnyType ( single_accounting );
        }

        else
            return 0;
    }

    return 0;
}


float ACCOUNTING_getTotalBilledAllYearByType ( ACCOUNTING_T accounting,  AProductKey key , AccountType type_accounting )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;
            return PRODUCT_ACCOUNTING_getTotalBilledAllYearByType ( single_accounting, type_accounting );
        }

        else
            return 0;
    }

    return 0;
}

void ACCOUNTING_destroy ( ACCOUNTING_T accounting )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    TRIE_destroy ( cont->product_list );
    free ( cont );
}

STRING_ARRAY_T ACCOUNTING_getNonBilledProducts ( ACCOUNTING_T accounting )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    STRING_ARRAY_T buff = STRING_ARRAY_init();
    TRIE_getAllKeysWithoutInfo ( cont->product_list, buff );
    return buff;
}


void ACCOUNTING_deleteProductAccounting ( ACCOUNTING_T accounting, AProductKey key )
{   float totalBought = 0;
    float totalBoughtByMonth = 0;
    float totalBilledByMonth = 0;
    int i;
    ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    PRODUCT_ACCOUNTING_T single_accounting;
    TRIE_T tr = cont->product_list;
    NODO_T nodo= TRIE_search ( tr, key );
    Info info=NULL;

    if ( nodo )
    {   info = TRIE_getNodeInfo ( nodo );

        if ( info )
        {   single_accounting = ( PRODUCT_ACCOUNTING_T ) info;

            for ( i=0; i < MAXMONTH; i++ )
            {   totalBilledByMonth=PRODUCT_ACCOUNTING_getTotalBilledByMonthByAnyType ( single_accounting, i );
                totalBoughtByMonth =PRODUCT_ACCOUNTING_getTotalBoughtByMonth ( single_accounting, i );
                cont->month_total_billed[i]-= totalBilledByMonth;
                cont->month_total_single_purch[i]-= totalBoughtByMonth;
                totalBought+=totalBoughtByMonth;
            }

            cont->total_prod_comp-=totalBought;
            /*PRODUCT_ACCOUNTING_deleteProductPurchases(single_accounting);*/
            TRIE_delete ( tr, key );
        }
    }
}



int ACCOUNTING_getTotalBoughtProductsAllYear (  ACCOUNTING_T accounting )
{   ACCOUNTING *cont = ( ACCOUNTING * ) accounting;
    return cont->total_prod_comp;
}


float ACCOUNTING_getTotalBilledInMonthInterval ( ACCOUNTING_T accounting, AMonth month1 , AMonth month2 )
{   float total = 0;
    int i ;
    ACCOUNTING *cont = ( ACCOUNTING * ) accounting;

    for ( i=MONTHOFFSET ( month1 ) ; i < MONTHOFFSET ( month2 ); i++ )
    {   total+=cont->month_total_billed[i];
    }

    return total;
}

int ACCOUNTING_totalBoughtInMonthInterval ( ACCOUNTING_T accounting, AMonth month1 , AMonth month2 )
{   int total = 0;
    int i ;
    ACCOUNTING *cont = ( ACCOUNTING * ) accounting;

    for ( i=MONTHOFFSET ( month1 ) ; i < MONTHOFFSET ( month2 ); i++ )
    {   total+=cont->month_total_single_purch[i];
    }

    return total;
}

