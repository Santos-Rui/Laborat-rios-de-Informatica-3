
#ifndef TRIE_H                  /*mudei TAD_trie para trie*/
#define TRIE_H
#define ARRAY_SIZE 64
#include "string_array.h"
typedef char * Key;
typedef void * Info;
typedef struct TRIE * TRIE_T;
typedef struct NODO * NODO_T;


STRING_ARRAY_T TRIE_getAllKeysWithoutInfo( TRIE_T, STRING_ARRAY_T );


STRING_ARRAY_T TRIE_getAllKeysWithInfo( TRIE_T, STRING_ARRAY_T );

TRIE_T TRIE_insert(TRIE_T, Key, Info);
TRIE_T TRIE_init();

NODO_T TRIE_search (TRIE_T, Key);     

void TRIE_destroy( TRIE_T);
void TRIE_delete(TRIE_T, Key);

NODO_T TRIE_getFirtstCharKeyNode(char, TRIE_T);

void TRIE_setNodeInfo(NODO_T, Info);
Info TRIE_getNodeInfo ( NODO_T node );


STRING_ARRAY_T TRIE_getAllKeysFromNode( NODO_T, STRING_ARRAY_T, char *, int);

int TRIE_getTotalKeys ( TRIE_T );
int TRIE_getTotalKeysBeginningWith ( char, TRIE_T, char);



STRING_ARRAY_T TRIE_getAllKeys(TRIE_T, STRING_ARRAY_T);



void TRIE_map ( TRIE_T trie, void (*function)(NODO_T, void *), void * arg);

void TRIE_getLetters (TRIE_T trie, int v []);



#endif

