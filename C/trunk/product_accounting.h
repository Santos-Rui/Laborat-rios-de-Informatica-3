#ifndef PRODUCT_ACCOUNTING_H
#define PRODUCT_ACCOUNTING_H



typedef struct PRODUCT_ACCOUNTING * PRODUCT_ACCOUNTING_T;

PRODUCT_ACCOUNTING_T PRODUCT_ACCOUNTING_init();
PRODUCT_ACCOUNTING_T PRODUCT_ACCOUNTING_create(char type_accounting, int month,  float value, int quantity);
PRODUCT_ACCOUNTING_T PRODUCT_ACCOUNTING_update ( PRODUCT_ACCOUNTING_T product_accounting, int month,   char type_accounting, float value, int quantity );

void PRODUCT_ACCOUNTING_deleteProductPurchases(PRODUCT_ACCOUNTING_T pat);
float PRODUCT_ACCOUNTING_getTotalBilledByMonthByType(PRODUCT_ACCOUNTING_T pat, int month, char type_accounting);
float PRODUCT_ACCOUNTING_getTotalBilledByMonthByAnyType(PRODUCT_ACCOUNTING_T pat, int month);
float PRODUCT_ACCOUNTING_getTotalBilledAllYearByType(PRODUCT_ACCOUNTING_T pat, char type_accounting);
float PRODUCT_ACCOUNTING_getTotalBilledAllYearAnyType(PRODUCT_ACCOUNTING_T pat);
int PRODUCT_ACCOUNTING_getTotalQuantityByMonthByType(PRODUCT_ACCOUNTING_T pat, int month, char type_accounting);
int PRODUCT_ACCOUNTING_getTotalQuantityByMonthByAnyType(PRODUCT_ACCOUNTING_T pat, int month);
int PRODUCT_ACCOUNTING_getTotalQuantityAllYearByType(PRODUCT_ACCOUNTING_T pat, char type_accounting);
int PRODUCT_ACCOUNTING_getTotalQuantityAllYearAnyType(PRODUCT_ACCOUNTING_T pat);
int PRODUCT_ACCOUNTING_getTotalBoughtByMonth ( PRODUCT_ACCOUNTING_T pat, int month );

#endif
