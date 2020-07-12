#include <stdio.h>
#include <stdlib.h>      /*mudei TAD_trie_T para TRIE_T*/
#include <string.h>      /*mudei TRIE_T para TRIE*/
#include "string_array.h"
#include "trie.h"
#include "bool.h"
#define MAX_ALPH 26
#define KEY_SIZE 32
#define OFFSET(i) (i-'0')
#define KEY_HAS_VALUE 1
#define KEY_HASNOT_VALUE 2
#define DEFAULT_KEY 0
typedef struct trie_node
{   struct trie_node *nodo[ARRAY_SIZE]; /*do 0 ao Z, em caps*/

    struct trie_node *aux;
    Info info;
    int control;
} NODO;

typedef struct NODO
{

    int nr_letters[MAX_ALPH];
    NODO *raiz;
    int total_keys;



} TRIE;


static NODO *novoNodo()
{   int i;
    NODO *a = ( NODO * ) malloc ( sizeof ( NODO ) );

    for ( i=0; i<ARRAY_SIZE; i++ )
    {   a -> nodo[i] = NULL;
    }

    a -> aux = NULL;
    a -> control = 0;
    a ->info = NULL;
    return a;
}


static int nodoLivre ( NODO *nodo )
{   int i;

    for ( i=0; i < ARRAY_SIZE; i++ )
        if ( nodo->nodo[i] )
            return 0;

    return 1;
}

static int append_char2str ( char a , char *buff, int buff_index )
{   buff[buff_index] = a;
    buff[buff_index + 1] = '\0';
    buff_index++;
    return buff_index;
}

TRIE_T TRIE_init()   /*cria a raiz*/
{   TRIE *raiz= ( TRIE * ) malloc ( sizeof ( TRIE ) );
    TRIE_T root=NULL;
    int i = 0;
    raiz->raiz = novoNodo();

    for ( i=0; i<MAX_ALPH; i++ )
        raiz->nr_letters[i]=0;

    raiz->total_keys = 0;
    root = ( TRIE_T ) raiz;
    return root;
}


TRIE_T TRIE_insert ( TRIE_T trie, Key key, Info info )
{   int  nivel, tam;
    int i = 0;
    TRIE *raiz= ( TRIE * ) trie;
    NODO *ap = raiz->raiz;
    tam = strlen ( key );
    raiz->nr_letters[key[0]-'A']++;

    for ( nivel = 0; nivel < tam; nivel++ )
    {   i = OFFSET ( key[nivel] );

        if ( ap->nodo[i] == NULL )
        {   ap->nodo[i] = novoNodo();
        }

        ap = ap->nodo[i];
    }

    if ( ap->control==0 )
        raiz->total_keys++;

    ap->control = 1;
    ap->info = info;
    return trie;

}

NODO_T TRIE_search ( TRIE_T trie, Key key )
{   TRIE *raiz = ( TRIE * ) trie;
    NODO *ap = raiz->raiz;
    int i, nivel, tam;

    if ( ap == NULL )
    {   return NULL;
    }

    tam = strlen ( key );

    for ( nivel = 0; nivel < tam; nivel++ )
    {   i = OFFSET ( key[nivel] );

        if ( ap->nodo[i] == NULL )
        {   return NULL;
        }

        ap = ap->nodo[i];
    }

    if ( ap&&ap->control )
        return ( NODO_T ) ap;

    return NULL;
}



static int eFolha ( NODO *nodo )
{   return nodo->control;
}

NODO_T TRIE_getFirtstCharKeyNode ( char a, TRIE_T t )
{   TRIE *raiz = ( TRIE * ) t;
    return ( NODO_T ) raiz->raiz->nodo[OFFSET ( a )];
}
int TRIE_getTotalKeysBeginningWith ( char a, TRIE_T t , char offset )
{   TRIE *raiz = ( TRIE * ) t;
    int total = raiz->nr_letters[ a - offset];
    return ( total );
}

int TRIE_getTotalKeys ( TRIE_T t )
{   TRIE *raiz = ( TRIE * ) t;
    return raiz->total_keys;
}

Info TRIE_getNodeInfo ( NODO_T node )
{   NODO *aux = ( NODO * ) node;
    return aux->info;
}
void TRIE_setNodeInfo ( NODO_T node, Info info )
{   NODO *aux = ( NODO * ) node;
    aux->info = info;
}
void TRIE_getLetters ( TRIE_T trie, int v [] )
{   TRIE *raiz = ( TRIE * ) trie;
    int i;

    for ( i=0; i < MAX_ALPH; i++ )
    {   v [i]= raiz->nr_letters[i];
    }
}


static int deleteHelper ( NODO *pNode, char key[], int level, int len )
{   if ( pNode )
    {   if ( level == len )
        {   if ( pNode->control )
            {   pNode->control = 0;

                if ( nodoLivre ( pNode ) )
                {   return 1;
                }

                return 0;
            }
        }

        else
        {   int index = OFFSET ( key[level] );

            if ( deleteHelper ( pNode->nodo[index], key, level+1, len ) )
            {   if ( pNode->nodo[index]->info )
                {   free ( pNode->nodo[index]->info );
                    pNode->nodo[index]->info =NULL;
                }

                free ( pNode->nodo[index] );
                pNode->nodo[index]=NULL;
                return ( !eFolha ( pNode ) && nodoLivre ( pNode ) );
            }
        }
    }

    return 0;
}
static void trie_free_list_push ( NODO **list, NODO *node )
{   node->aux = *list;
    *list = node;
}

static NODO *trie_free_list_pop ( NODO **list )
{   NODO *result;
    result = *list;
    *list = result->aux;
    return result;
}
void TRIE_destroy ( TRIE_T t )
{   TRIE *trie =  ( TRIE * ) t;
    NODO *free_list;
    NODO *node;
    int i;
    free_list = NULL;

    if ( trie->raiz!= NULL )
    {   trie_free_list_push ( &free_list, trie->raiz );
    }

    while ( free_list != NULL )
    {   node = trie_free_list_pop ( &free_list );

        for ( i=0; i<ARRAY_SIZE; ++i )
        {   if ( node->nodo[i] != NULL )
            {   trie_free_list_push ( &free_list, node->nodo[i] );
            }
        }

        if ( node->info )
        {   free ( node->info );
            node->info =NULL;
        }

        free ( node );
    }

    free ( trie );
}

void TRIE_delete ( TRIE_T trie, Key key )
{   int len = strlen ( key );
    TRIE *raiz = ( TRIE * ) trie;
    NODO *ap = raiz->raiz;

    if ( len > 0 )
    {   if ( deleteHelper ( ap, key, 0, len ) &&raiz->total_keys )
            raiz->total_keys--;
    }
}


static void traverse_nodo ( NODO *t , void ( *function ) ( NODO_T, void * ), void *arg )
{   NODO *ap = t;
    int nivel = 0;

    if ( ap == NULL )
        return;

    if ( ap->control==1 )
    {   function ( ( NODO_T ) ap , arg );
    }

    for ( ; nivel < ARRAY_SIZE; nivel++ )
    {   if ( ap->nodo[nivel] != NULL )
        {   traverse_nodo ( ap->nodo[nivel],  function, arg );
        }
    }

    return;
}
static STRING_ARRAY_T get_Keys ( NODO *t, STRING_ARRAY_T buff , char *intern_buff, int buff_index , int hasValue )
{   NODO *ap = t;
    int nivel = 0;

    if ( ap == NULL || buff==NULL )
        return buff;

    if ( ap->control==1 )
    {   switch ( hasValue )
        {   case KEY_HAS_VALUE :
                if ( ap->info )
                    buff = STRING_ARRAY_insert ( buff, intern_buff );

                break;

            case KEY_HASNOT_VALUE :
                if ( ap->info==NULL )
                    buff = STRING_ARRAY_insert ( buff, intern_buff );

                break;

            case DEFAULT_KEY:
                buff = STRING_ARRAY_insert ( buff, intern_buff );
                break;
        }
    }

    for ( ; nivel < ARRAY_SIZE; nivel++ )
    {   if ( ap->nodo[nivel] != NULL )
        {   buff_index = append_char2str ( nivel + '0' , intern_buff, buff_index );
            get_Keys ( ap->nodo[nivel] , buff , intern_buff, buff_index , hasValue );
            buff_index--;
        }
    }

    return buff;
}

STRING_ARRAY_T TRIE_getAllKeysFromNode ( NODO_T t, STRING_ARRAY_T buff , char *intern_buff, int buff_index )
{   NODO *aux = ( NODO * ) t;
    return get_Keys ( aux, buff , intern_buff, buff_index , DEFAULT_KEY );
}
void TRIE_map ( TRIE_T trie , void ( *function ) ( NODO_T, void * ), void *arg )
{   TRIE *raiz = ( TRIE * ) trie;
    NODO *aux = raiz->raiz;
    traverse_nodo ( aux, function , arg );
}
STRING_ARRAY_T TRIE_getAllKeys ( TRIE_T trie , STRING_ARRAY_T buff )
{   TRIE *raiz = ( TRIE * ) trie;
    char intern_buff[ARRAY_SIZE];
    int buff_index = 0;
    NODO *aux = raiz->raiz;
    return get_Keys ( aux, buff , intern_buff, buff_index, DEFAULT_KEY );
}

STRING_ARRAY_T TRIE_getAllKeysWithoutInfo ( TRIE_T trie , STRING_ARRAY_T buff )
{   TRIE *raiz = ( TRIE * ) trie;
    char intern_buff[ARRAY_SIZE];
    int buff_index = 0;
    NODO *aux = raiz->raiz;
    return get_Keys ( aux, buff , intern_buff, buff_index, KEY_HASNOT_VALUE );
}
STRING_ARRAY_T TRIE_getAllKeysWithInfo ( TRIE_T trie , STRING_ARRAY_T buff )
{   TRIE *raiz = ( TRIE * ) trie;
    char intern_buff[ARRAY_SIZE];
    int buff_index = 0;
    NODO *aux = raiz->raiz;
    return get_Keys ( aux, buff , intern_buff, buff_index, KEY_HAS_VALUE );
}
/*int main()
{   return 0;
}*/



