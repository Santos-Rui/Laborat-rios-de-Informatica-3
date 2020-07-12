#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bool.h"
#include "string_array.h"
#define DEFAULT_SIZE 2048
typedef struct STRING_ARRAY
{

    char **strArray;

    int elems;

    int size;

} STRING_ARRAY;
char *strdup_st(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
            strcpy(dup, str);
        }
    return dup;
}

STRING_ARRAY_T STRING_ARRAY_init ()
{   STRING_ARRAY *array = ( STRING_ARRAY * ) malloc ( sizeof ( STRING_ARRAY ) );
    array->strArray = ( char ** ) malloc ( DEFAULT_SIZE*sizeof ( char * ) );
    array->elems =0;
    array->size =DEFAULT_SIZE;
    return ( STRING_ARRAY_T ) array;
}

STRING_ARRAY_T STRING_ARRAY_insert ( STRING_ARRAY_T strArr, char *str )
{   STRING_ARRAY *array = ( STRING_ARRAY * ) strArr;

    if ( array->elems==array->size )
    {   array->size = array->size*2;
        array->strArray = ( char ** ) realloc ( array->strArray, array->size*sizeof ( char * ) );
    }

    array->strArray[array->elems]= strdup_st ( str );
    array->elems++;
    return ( STRING_ARRAY_T ) array;
}

const char *STRING_ARRAY_getStringAtPos ( STRING_ARRAY_T strArr, int pos )
{   STRING_ARRAY *array = ( STRING_ARRAY * ) strArr;
    return (const char *)array->strArray[pos];
}

const char **STRING_ARRAY_getStringArrayPointer ( STRING_ARRAY_T strArr )
{   STRING_ARRAY *array = ( STRING_ARRAY * ) strArr;
    return (const char **)array->strArray;
}

int STRING_ARRAY_getNumElems ( STRING_ARRAY_T strArr )
{   STRING_ARRAY *array = ( STRING_ARRAY * ) strArr;
    return array->elems;
}
int STRING_ARRAY_getSize ( STRING_ARRAY_T strArr )
{   STRING_ARRAY *array = ( STRING_ARRAY * ) strArr;
    return array->size;
}
void STRING_ARRAY_destroy ( STRING_ARRAY_T strArr )
{   STRING_ARRAY *array = ( STRING_ARRAY * ) strArr;
    int i;

    for ( i=0; i < array->elems; i++ )
        free ( array->strArray[i] );

    free ( array->strArray );
    free ( array );
}
Boolean STRING_ARRAY_isEmpty ( STRING_ARRAY_T strArr )
{   STRING_ARRAY *array = ( STRING_ARRAY * ) strArr;
    Boolean isNotEmpty = false;

    if ( !array->elems )
        isNotEmpty = true;

    return isNotEmpty;
}







