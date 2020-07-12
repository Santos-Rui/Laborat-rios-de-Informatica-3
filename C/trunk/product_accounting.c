#include <stdlib.h>
#include "product_accounting.h"
#include "bool.h"
#define MAXMONTH 16
#define MAXSTR 32
#define MONTHOFFSET(m) m-1

typedef struct PRODUCT_ACCOUNTING
{   int   total_bought        [MAXMONTH];
    int   quantity_normal_mode[MAXMONTH];
    int   quantity_promo_mode [MAXMONTH];
    float total_billed_promo  [MAXMONTH];
    float total_billed_normal [MAXMONTH];
} PRODUCT_ACCOUNTING;

PRODUCT_ACCOUNTING_T PRODUCT_ACCOUNTING_init ( )
{   int i;
    PRODUCT_ACCOUNTING *single_accounting = ( PRODUCT_ACCOUNTING * ) malloc ( sizeof ( PRODUCT_ACCOUNTING ) );

    for ( i=0; i< MAXMONTH; i++ )
    {   single_accounting->total_billed_normal[i] = single_accounting->total_billed_promo[i] = 0.0;
        single_accounting->quantity_normal_mode[i] = single_accounting->quantity_promo_mode[i] = 0;
        single_accounting->total_bought[i]=0;
    }

    return ( PRODUCT_ACCOUNTING_T ) single_accounting;
}

PRODUCT_ACCOUNTING_T PRODUCT_ACCOUNTING_create ( char type_accounting, int month,  float value, int quantity )
{   PRODUCT_ACCOUNTING *product_accounting = ( PRODUCT_ACCOUNTING * ) PRODUCT_ACCOUNTING_init();

    switch ( type_accounting )
    {   case 'N':
            product_accounting->total_billed_normal[MONTHOFFSET ( month )]=value*quantity;
            product_accounting->quantity_normal_mode[MONTHOFFSET ( month )]=quantity;
            break;

        case 'P':
            product_accounting->total_billed_promo[MONTHOFFSET ( month )]=value*quantity;
            product_accounting->quantity_promo_mode[MONTHOFFSET ( month )]=quantity;
            break;
    }

    product_accounting->total_bought[MONTHOFFSET ( month )]++;
    return ( PRODUCT_ACCOUNTING_T ) product_accounting;
}
PRODUCT_ACCOUNTING_T PRODUCT_ACCOUNTING_update ( PRODUCT_ACCOUNTING_T product_accounting, int month,   char type_accounting, float value, int quantity )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) product_accounting;

    switch ( type_accounting )
    {   case 'N':
            pa->total_billed_normal[MONTHOFFSET ( month )]+= ( value*quantity );
            pa->quantity_normal_mode[MONTHOFFSET ( month )]+=quantity;
            break;

        case 'P':
            pa->total_billed_promo[MONTHOFFSET ( month )]+= ( value*quantity );
            pa->quantity_promo_mode[MONTHOFFSET ( month )]+=quantity;
            break;
    }

    pa->total_bought[MONTHOFFSET ( month )]++;
    return ( PRODUCT_ACCOUNTING_T ) pa;
}
PRODUCT_ACCOUNTING_T PRODUCT_ACCOUNTING_updateQuantityInMonthByType ( PRODUCT_ACCOUNTING_T pat, int month, char type_accounting, int value )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;

    switch ( type_accounting )
    {   case 'N':
            pa->quantity_normal_mode[MONTHOFFSET ( month )] = value;
            break;

        case 'P':
            pa->quantity_promo_mode[MONTHOFFSET ( month )] = value;
            break;
    }

    return ( PRODUCT_ACCOUNTING_T ) pa;
}



void PRODUCT_ACCOUNTING_deleteProductPurchases ( PRODUCT_ACCOUNTING_T pat )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    free ( pa );
}

float PRODUCT_ACCOUNTING_getTotalBilledByMonthByType ( PRODUCT_ACCOUNTING_T pat, int month, char type_accounting )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    float total = 0.0;

    switch ( type_accounting )
    {   case 'N':
            total= pa->total_billed_normal[MONTHOFFSET ( month )];
            break;

        case 'P':
            total= pa->total_billed_promo[MONTHOFFSET ( month )] ;
            break;
    }

    return total;
}

float PRODUCT_ACCOUNTING_getTotalBilledByMonthByAnyType ( PRODUCT_ACCOUNTING_T pat, int month )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    return ( pa->total_billed_normal[MONTHOFFSET ( month )] + pa->total_billed_promo[MONTHOFFSET ( month )] );
}

float PRODUCT_ACCOUNTING_getTotalBilledAllYearByType ( PRODUCT_ACCOUNTING_T pat, char type_accounting )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    float total = 0.0;
    int i;

    switch ( type_accounting )
    {   case 'N':
            for ( i=0; i<MAXMONTH; i++ )
                total += pa->total_billed_normal[i];

            break;

        case 'P':
            for ( i=0; i<MAXMONTH; i++ )
                total += pa->total_billed_promo[i];

            break;
    }

    return total;
}


float PRODUCT_ACCOUNTING_getTotalBilledAllYearAnyType ( PRODUCT_ACCOUNTING_T pat )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    float totalN = 0.0;
    float total = 0.0;
    float totalP = 0.0;
    int i;

    for ( i=0; i<MAXMONTH; i++ )
    {   totalP += pa->total_billed_normal[i] ;
        totalN += pa->total_billed_promo[i];
    }

    total = totalN +totalP;
    return total;
}

int PRODUCT_ACCOUNTING_getTotalQuantityByMonthByType ( PRODUCT_ACCOUNTING_T pat, int month, char type_accounting )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;

    int total = 0;
    switch ( type_accounting )
    {   case 'N':
            total= pa->quantity_normal_mode[MONTHOFFSET ( month )];

        case 'P':
            total = pa->quantity_promo_mode[MONTHOFFSET ( month )];
    }

    return total;
}

int PRODUCT_ACCOUNTING_getTotalQuantityByMonthByAnyType ( PRODUCT_ACCOUNTING_T pat, int month )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    return ( pa->quantity_normal_mode[MONTHOFFSET ( month )] + pa->quantity_promo_mode[MONTHOFFSET ( month )] );
}
int PRODUCT_ACCOUNTING_getTotalQuantityAllYearByType ( PRODUCT_ACCOUNTING_T pat, char type_accounting )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    int i, total = 0;

    switch ( type_accounting )
    {   case 'N':
            for ( i=0; i<MAXMONTH; i++ )
                total += pa->quantity_normal_mode[i];

            break;

        case 'P':
            for ( i=0; i<MAXMONTH; i++ )
                total += pa->quantity_promo_mode[i];
    }

    return total;
}


int PRODUCT_ACCOUNTING_getTotalQuantityAllYearAnyType ( PRODUCT_ACCOUNTING_T pat )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    int totalN = 0;
    int total  = 0;
    int totalP = 0;
    int i;

    for ( i=0; i<MAXMONTH; i++ )
    {   totalP += pa->quantity_normal_mode[i] ;
        totalN += pa->quantity_normal_mode[i];
    }

    total = totalN +totalP;
    return total;
}


int PRODUCT_ACCOUNTING_getTotalBoughtByMonth ( PRODUCT_ACCOUNTING_T pat, int month )
{   PRODUCT_ACCOUNTING *pa = ( PRODUCT_ACCOUNTING * ) pat;
    return pa->total_bought[MONTHOFFSET ( month )];
}








