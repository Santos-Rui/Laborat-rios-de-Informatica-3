#include "bool.h"

typedef struct PRODUCT_PURCHASES * PRODUCT_PURCHASE_T;
typedef char * PPClientKey;

typedef char * PPProductKey;

PRODUCT_PURCHASE_T PRODUCT_PURCHASES_init();
PRODUCT_PURCHASE_T PRODUCT_PURCHASES_create ( PPProductKey pkey , PPClientKey ckey,  char type_purchase, int month, int quantity );
PRODUCT_PURCHASE_T PRODUCT_PURCHASES_update ( PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase, int quantity );
void PRODUCT_PURCHASES_delete(PRODUCT_PURCHASE_T product_purchases);

Boolean deleteQuantityInMonthByType(PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase, int quantity );

char * getProductKey ( PRODUCT_PURCHASE_T product_purchases);

char * getClientKey (PRODUCT_PURCHASE_T product_purchases);

int getTotalQuantityInMonthByType(PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase);

int getTotalQuantityAllYearbyType(PRODUCT_PURCHASE_T product_purchases, char type_purchase);

int getTotalQuantityAllYearbyAnyType(PRODUCT_PURCHASE_T product_purchases);

int getTotalBoughtProductOfClient();

int setTotalQuantityInMonthByType(PRODUCT_PURCHASE_T product_purchases, int month, char type_purchase);

PRODUCT_PURCHASE_T PRODUCT_PURCHASES_createDummyPurchase ( PPClientKey key);



