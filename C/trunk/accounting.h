#ifndef ACCOUNTING_H
#define ACCOUNTING_H
#include "product_accounting.h"
#include "string_array.h"
typedef struct ACCOUNTING * ACCOUNTING_T;
typedef char* AProductKey;
typedef int AQuantity;
typedef int AMonth;
typedef float PriceValue;
typedef char AccountType;
typedef float TotalValue;
typedef int AQuantityPromo;

typedef int AQuantityNormal;



ACCOUNTING_T ACCOUNTING_init();

ACCOUNTING_T ACCOUNTING_insertProductKey ( ACCOUNTING_T, AProductKey);

ACCOUNTING_T ACCOUNTING_insertProductAccounting ( ACCOUNTING_T, AProductKey, AMonth, AccountType, PriceValue, AQuantity);


PRODUCT_ACCOUNTING_T ACCOUNTING_search ( ACCOUNTING_T, AProductKey );

void ACCOUNTING_deleteProductAccounting ( ACCOUNTING_T, AProductKey );

void ACCOUNTING_destroy (ACCOUNTING_T);



int ACCOUNTING_getTotalBoughtProductsAllYear(ACCOUNTING_T);

int ACCOUNTING_getTotalQuantityInMonthByType ( ACCOUNTING_T , AProductKey , AMonth , AccountType);

int ACCOUNTING_getTotalQuantityByMonthByAnyType(ACCOUNTING_T pat, AProductKey , AMonth);

int ACCOUNTING_getTotalQuantityAllYearByType( ACCOUNTING_T , AProductKey ,  AccountType);

int ACCOUNTING_getTotalQuantityAllYearAnyType( ACCOUNTING_T , AProductKey);


float ACCOUNTING_getTotalBilledInMonthByType ( ACCOUNTING_T , AProductKey , AMonth , AccountType);

float ACCOUNTING_getTotalBilledByMonthByAnyType(ACCOUNTING_T,  AProductKey , AMonth);

float ACCOUNTING_getTotalBilledAllYearByType(ACCOUNTING_T,  AProductKey , AccountType);

float ACCOUNTING_getTotalBilledAllYearAnyType(ACCOUNTING_T,  AProductKey);


float ACCOUNTING_getTotalBilledInMonthInterval ( ACCOUNTING_T , AMonth, AMonth );

int ACCOUNTING_totalBoughtInMonthInterval ( ACCOUNTING_T a, AMonth , AMonth );


STRING_ARRAY_T ACCOUNTING_getNonBilledProducts ( ACCOUNTING_T);


#endif /* !ACCOUNTING_H */

