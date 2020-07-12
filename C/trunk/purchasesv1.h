#ifndef PURCHASES_H
#define PURCHASES_H
#include "trie.h"
typedef struct PURCHASES * PURCHASES_T;
typedef char* PProductKey;
typedef char* PClientKey;
typedef int PQuantity;
typedef int PMonth;
typedef char PurchaseType;
typedef int PQuantityPromo;

typedef int PQuantityNormal;

typedef int PAllocatedSize;


PURCHASES_T PURCHASES_init();

PURCHASES_T PURCHASES_insertClient ( PURCHASES_T, PClientKey);

PURCHASES_T PURCHASES_insertClientProduct( PURCHASES_T, PClientKey, PProductKey);

PURCHASES_T PURCHASES_insertClientProducts ( PURCHASES_T, PProductKey);

PURCHASES_T PURCHASES_insertWith ( PURCHASES_T, PClientKey, PProductKey, PMonth, PurchaseType, PQuantity  );

TRIE_T getList(PURCHASES_T purchases);

int PURCHASES_exists_client ( PURCHASES_T, PClientKey);

int PURCHASES_exists_clientProduct ( PURCHASES_T, PClientKey, PProductKey);


int PURCHASES_search_clientProduct ( PURCHASES_T, PClientKey, PProductKey,PMonth, PQuantityNormal* , PQuantityPromo*);

void PURCHASES_delete_client ( PURCHASES_T, PClientKey);

void PURCHASES_delete_clientProduct ( PURCHASES_T, PClientKey, PProductKey);

void PURCHASES_destroy (PURCHASES_T);

/* querie 8 */
char ** PURCHASES_getProductClientList ( PURCHASES_T , PProductKey, PAllocatedSize *);


/* querie 9 */
char ** PURCHASES_getClientMostBoughtProductListByMonthDesc ( PURCHASES_T , PProductKey , PMonth);


/* querie 10 */
char ** PURCHASES_getClientListAllMonth ( PURCHASES_T , PAllocatedSize *);


/* querie 11 */
void getTotalClientsAndPurshasesList (PURCHASES_T, int total_purshases_by_month[], int total_clients_by_month[]);


/* querie 12 */
char ** getNthMostSoldProductList( PURCHASES_T, PAllocatedSize * );

/*querie 13 */

char ** get_client_3MostBoughtProducts(PURCHASES_T, int *);

/*querie 14 */

int getTotalClientsWithNoPurchases(PURCHASES_T);

int getTotalProductsNotBought (PURCHASES_T);

#endif /* !PURCHASES_H */

