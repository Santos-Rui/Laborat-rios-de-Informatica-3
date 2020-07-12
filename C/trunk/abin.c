#include <stdio.h>
#include <stdlib.h>
#include "abin.h"
#include "avl.h"

typedef struct avl_table *ABin;



ABin_T ABin_init ( Compare comp, void *extra )
{   ABin avl =  avl_create ( comp, extra, NULL );
    return ( ABin_T ) avl;
}

ABinInfo ABin_insert ( ABin_T abin, ABinInfo info )
{   info = ( ABinInfo ) avl_insert ( ( struct avl_table * ) abin, info );
    return ( ABinInfo ) info;
}

ABinInfo ABin_search ( ABin_T abin, ABinInfo info )
{   info = avl_find ( ( struct avl_table * ) abin, info );
    return ( ABinInfo ) info;
}

ABinInfo ABin_delete ( ABin_T abin, ABinInfo info )
{   info = avl_delete ( ( struct avl_table * ) abin , info );
    return ( ABinInfo ) info;
}

void ABin_destroy ( ABin_T abin )
{   avl_destroy ( ( struct avl_table * ) abin, NULL );
}

Iterator_T Iterator_create()
{   struct avl_traverser *trav = ( struct avl_traverser * ) malloc ( sizeof ( struct avl_traverser ) );
    return ( Iterator_T ) trav;
}
void Iterator_init ( Iterator_T it, ABin_T abin )
{   avl_t_init ( ( struct avl_traverser * ) it, ( struct avl_table * ) abin );
}
ABinInfo Iterator_First ( Iterator_T it, ABin_T abin )
{   ABinInfo info = avl_t_first ( ( struct avl_traverser * ) it, ( struct avl_table * ) abin  ) ;
    return info;
}
ABinInfo Iterator_Last ( Iterator_T it, ABin_T abin )
{   ABinInfo info = avl_t_last ( ( struct avl_traverser * ) it, ( struct avl_table * ) abin );
    return info;
}
ABinInfo Iterator_Next ( Iterator_T it )
{   ABinInfo info = avl_t_next ( ( struct avl_traverser * ) it );
    return info;
}
ABinInfo Iterator_Prev ( Iterator_T it )
{   ABinInfo info = avl_t_prev ( ( struct avl_traverser * ) it );
    return info;
}
void Iterator_T_destroy ( Iterator_T it )
{   free ( ( struct avl_traverser * ) it );
    it = NULL;
}














