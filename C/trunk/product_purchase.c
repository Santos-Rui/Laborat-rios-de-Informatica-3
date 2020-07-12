#include <stdlib.h>
#include <string.h>
#include "product_purchase.h"
#include "bool.h"
#define MAXMONTH 16
#define MAXSTR 32
#define MONTHOFFSET(m) m-1

typedef struct PRODUCT_PURCHASES
{   int quantity_normal_mode[MAXMONTH];
    int quantity_promo_mode[MAXMONTH];
    char clientKey[MAXSTR];
    char prodKey[MAXSTR];
    int total_bought_by_client;
} PRODUCT_PURCHASES;


PRODUCT_PURCHASE_T PRODUCT_PURCHASES_init()
{   int i;
    PRODUCT_PURCHASE_T ppurch = ( PRODUCT_PURCHASE_T ) malloc ( sizeof ( PRODUCT_PURCHASES ) );

    for ( i=0; i< MAXMONTH; i++ )
    {   ppurch->quantity_normal_mode[i] = ppurch->quantity_promo_mode[i] = 0;
    }

    ppurch->total_bought_by_client = 0;
    return ppurch;
}

PRODUCT_PURCHASE_T PRODUCT_PURCHASES_update ( PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase, int quantity )
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

PRODUCT_PURCHASE_T PRODUCT_PURCHASES_create ( PPProductKey pkey, PPClientKey ckey,  char type_purchase, int month, int quantity )
{   PRODUCT_PURCHASE_T product_purchases = PRODUCT_PURCHASES_init();
    strcpy ( product_purchases->clientKey, ckey );
    strcpy ( product_purchases->prodKey, pkey );

    switch ( type_purchase )
    {   case 'N':
            product_purchases->quantity_normal_mode[MONTHOFFSET ( month )]=quantity;
            break;

        case 'P':
            product_purchases->quantity_promo_mode[MONTHOFFSET ( month )]=quantity;
            break;
    }

    product_purchases->total_bought_by_client+=quantity;
    return product_purchases;
}


void PRODUCT_PURCHASES_delete ( PRODUCT_PURCHASE_T product_purchases )
{   PRODUCT_PURCHASES *prod = ( PRODUCT_PURCHASES * ) product_purchases;
    free ( prod );
    prod=NULL;
}

Boolean deleteQtyInMonthByType ( PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase, int quantity )
{   Boolean deleted = false;

    switch ( type_purchase )
    {   case 'N':
            if ( product_purchases->quantity_normal_mode[MONTHOFFSET ( month )] )
            {   product_purchases->quantity_normal_mode[MONTHOFFSET ( month )]-=quantity;
                deleted = true;
            }

            break;

        case 'P':
            if ( product_purchases->quantity_normal_mode[MONTHOFFSET ( month )] )
            {   product_purchases->quantity_promo_mode[MONTHOFFSET ( month )]-=quantity;
                deleted = true;
            }

            break;
    }
    if(deleted)
    product_purchases->total_bought_by_client-=quantity;

    return deleted;
}

char *getProductKey ( PRODUCT_PURCHASE_T product_purchases ){


}

char *getClientKey ( PRODUCT_PURCHASE_T product_purchases ){


}

int getTotalQtyInMonthByType ( PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase );

int getTotalQtyAllYearbyType ( PRODUCT_PURCHASE_T product_purchases, char type_purchase );

int getTotalQtyAllYearbyAnyType ( PRODUCT_PURCHASE_T product_purchases );

int getTotalBoughtProductOfClient();

int setTotalQtyInMonthByType ( PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase );

PRODUCT_PURCHASE_T PRODUCT_PURCHASES_createDummyPurchase ( PPClientKey key );





