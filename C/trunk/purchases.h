#ifndef PURCHASES_H
#define PURCHASES_H

typedef struct PURCHASES * PURCHASES_T;
typedef char* PProductKey;
typedef char* PClientKey;
typedef int Quantity;
typedef int Month;
typedef char BillType;
typedef int QuantityPromo;

typedef int QuantityNormal;

typedef int AllocatedSize;


PURCHASES_T PURCHASES_init();

PURCHASES_T PURCHASES_insertClient ( PURCHASES_T, PClientKey);

PURCHASES_T PURCHASES_insertClientProduct( PURCHASES_T, PClientKey, PProductKey);

PURCHASES_T PURCHASES_insertClientProducts ( PURCHASES_T purchases, PProductKey pkey );

PURCHASES_T PURCHASES_insertWith ( PURCHASES_T, PClientKey, PProductKey, Month, BillType, Quantity  );



int PURCHASES_exists_client ( PURCHASES_T, PClientKey);

int PURCHASES_exists_clientProduct ( PURCHASES_T, PClientKey, PProductKey);


int PURCHASES_search_clientProduct ( PURCHASES_T, PClientKey, PProductKey, Month, QuantityNormal* , QuantityPromo*);

void PURCHASES_delete_client ( PURCHASES_T, PClientKey);

void PURCHASES_delete_clientProduct ( PURCHASES_T, PClientKey, PProductKey);

void PURCHASES_destroy (PURCHASES_T);

/* querie 8 */
STRING_ARRAY_T PURCHASES_getProductClientList ( PURCHASES_T , PProductKey);


/* querie 9 */
STRING_ARRAY_T PURCHASES_getClientMostBoughtProductListByMonthDesc ( PURCHASES_T , PProductKey , Month);


/* querie 10 */
STRING_ARRAY_T  PURCHASES_getClientListAllMonth ( PURCHASES_T );


/* querie 11 */
void getTotalClientsAndPurshasesList (PURCHASES_T, int total_purshases_by_month[], int total_clients_by_month[]);


/* querie 12 */
char ** getNthMostSoldProductList( PURCHASES_T, AllocatedSize * );

/*querie 13 */

char ** get_client_3MostBoughtProducts(PURCHASES_T, int *);

/*querie 14 */

int getTotalClientsWithNoPurchases(PURCHASES_T);

int getTotalProductsNotBought (PURCHASES_T);

#endif /* !PURCHASES_H */

