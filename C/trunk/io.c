#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "product_cat.h"
#include "client_cat.h"
#include "purchases.h"
#include "accounting.h"
#include "io.h"
#define MAXSTR 32
static int tot = 0;
int multiple20 ( int x )
{   while ( x%20!=0 ) x++;

    return x;
}

int readFiles ( void *PRODUCT_CAT  ,void *CLIENT_CAT, void *ACCOUNTING, void *SALES, int type_selection, int max_buff, char *nomefich, int *validated )
{   FILE *fich ;
    int lines, n_token, mes,quantidade, val, isCodC, isCodP, v[26], v2[26], i;
    char buffer[MAXBUFF], * token=NULL, *subtoken=NULL, *str=NULL, *codigoC=NULL, *codigoP=NULL;
    char promo;
    double preco, total;
    clock_t inicial, final;
    lines = n_token= mes = quantidade = val = isCodC = isCodP = promo= 0;
    preco = total = 0.0;

    for ( i=0; i< 26; v2[i++]=0 );

    fich= fopen ( nomefich, "r" );
    inicial = clock();

    if ( fich != NULL )
    {   while ( fgets ( buffer, max_buff, fich ) != NULL )
        {   switch ( type_selection )
            {   case FILE_CLIENT :
                    token = strtok ( buffer,"\r\n" );
                    CLIENT_CAT = CLIENT_CAT_insert ( CLIENT_CAT, token );
                    SALES = PURCHASES_insertClient ( SALES, token );
                    break;

                case FILE_PRODUCT:
                    token = strtok ( buffer,"\r\n" );
                    PRODUCT_CAT = PRODUCT_CAT_insert ( PRODUCT_CAT, token );
                    ACCOUNTING =  ACCOUNTING_insertProductKey ( ACCOUNTING, token );
                    break;

                case FILE_SALES:
                    token = strtok ( buffer, "\n\r" );

                    for ( str= token, n_token = 0; ; str = NULL, n_token++ )
                    {   subtoken = strtok ( str, " \n\r" );

                        if ( subtoken == NULL )
                            break;

                        switch ( n_token )
                        {   case 0:
                                codigoP = ( char * ) malloc ( sizeof ( char ) *strlen ( subtoken )+1 );
                                strcpy ( codigoP, subtoken );
                                break;

                            case 1:
                                preco = atof ( subtoken );
                                break;

                            case 2:
                                quantidade = atoi ( subtoken );
                                break;

                            case 3:
                                promo = subtoken[0];
                                break;

                            case 4:
                                codigoC = ( char * ) malloc ( sizeof ( char ) *strlen ( subtoken )+1 );
                                strcpy ( codigoC, subtoken );
                                break;

                            case 5:
                                mes = atoi ( subtoken );
                                break;

                            default:
                                n_token = 0;
                                break;
                        }
                    }

                    isCodC+=!CLIENT_CAT_search ( CLIENT_CAT ,codigoC );

                    if ( CLIENT_CAT_search ( CLIENT_CAT ,codigoC ) )
                        isCodP+=!PRODUCT_CAT_search ( PRODUCT_CAT ,codigoP );

                    if ( PRODUCT_CAT_search ( PRODUCT_CAT ,codigoP ) && CLIENT_CAT_search ( CLIENT_CAT,codigoC ) )
                    {   val ++;
                        total+= ( preco* ( ( double ) quantidade ) );
                        tot+=quantidade;
                        v2[codigoP[0]-'A']++;
                        ACCOUNTING_insertProductAccounting ( ACCOUNTING ,codigoP, mes, promo, preco, quantidade  );
                        PURCHASES_insertWith ( SALES, codigoC, codigoP, mes, promo, quantidade  );
                        PURCHASES_insertClientProduct(SALES, codigoC, codigoP);
                    }

                    break;
            }

            lines++;
        }

        fclose ( fich );
    }

    else perror ( nomefich );

    final = clock();
    printf ( "Tempo %f \n", ( float ) ( final-inicial ) /CLOCKS_PER_SEC );

    if ( type_selection == FILE_SALES )
    {   printf ( " Linhas de compras: %d\n"
                 " Compras Validadas: %d\n"
                 " Códigos de Cliente inexistentes: %d\n"
                 " Códigos de Produto inexistentes: %d\n"
                 " Total de Inválidas: %d\n", lines, val, isCodC, isCodP, lines-val );
        printf ( "--------------------------------------------\n" );
        printf ( " Lista de Compras = %d\n"
                 " Faturacao Anual Total: %f\n", val, total );
        printf ( "---------------------------------------------\n" );
        printf ( "--CODIGOS DE PRODUTOS POR LETRA NO CATÁLOGO--\n" );
        printf ( "---------------------------------------------\n" );
        PRODUCT_CAT_getLetters ( PRODUCT_CAT, v );

        for ( i=0; i< 26; i++ )
            printf ( " %c %d \n", i+'A', v[i] );

        printf ( "---------------------------------------------\n" );
        printf ( " --CODIGOS DE CLIENTE POR LETRA NO CATÁLOGO--\n" );
        printf ( "---------------------------------------------\n" );

        for ( i=0; i< 26; v[i++]=0 );

        CLIENT_CAT_getLetters ( CLIENT_CAT, v );

        for ( i=0; i< 26; i++ )
            printf ( " %c %d \n", i+'A', v[i] );

        printf ( " ---------------------------------------------\n" );
        printf ( " --CODIGOS DE PRODUTOS POR LETRA NAS COMPRAS--\n" );
        printf ( "----------------------------------------------\n" );

        for ( i=0; i< 26; i++ )
            printf ( " %c %d \n", i+'A', v2[i] );

        printf ( " ---------------------------------------------\n" );

        printf ( " -----------------    %d    --------------\n", tot );
        *validated = val;
    }

    return lines;
}

void free_buffered_strings ( char **buff, int totalRead )
{   int i;
    totalRead = multiple20 ( totalRead );

    for ( i=0; i < totalRead; i++ )
    {   free ( buff[i] );
        buff[i]=NULL;
    }

    free ( buff );
    buff = NULL;
}

char **malloc_buffered_strings ( int totalRead, int max_buff )
{   int i;
    char **buff;
    totalRead = multiple20 ( totalRead );
    buff = ( char ** ) malloc ( sizeof ( char * ) *totalRead );

    if ( buff==NULL ) return NULL;

    for ( i=0; i < totalRead; i++ )
    {   buff[i]= ( char * ) malloc ( sizeof ( char ) *max_buff );
    }

    return buff;
}



void navigation ( char **nav, int lines )
{   int r, x, err, i;
    char ch;
    i = lines;

    while ( ( i % 20 ) !=0 )
    {   i++;
    }

    r= 0;

    do
    {   if ( r!= i&&r>=0 )
        {   printf ( "\033[2J\033[1;1H\n" );
            printf ( "Página %d de %d \n", ( r/20 )+1 , ( i/20 ) );
            printf ( "TOTAL: %d\n", lines );

            for ( x=r; x<r+20; x++ )
                for ( x=r; x<r+20; x++ )
                    if ( nav[x] )
                        printf ( "%s\n", nav[x] );

                    else printf ( "\n" );
        }

        if ( r<lines )
        {   printf ( "Introduza +/- para incrementar/decrementar 1 página, \nseguido de [ENTER](s para sair).\n" );
            printf ( "Sugestão:Introduza múltiplos +/- para múltiplas páginas.\n" );
        }

        err = scanf ( " %c", &ch );

        if ( err==0 ) return;

        switch ( ch )
        {   case '+' :
                if ( r<lines )
                    r+=20;

                break;

            case '-':
                if ( r>0 )
                    r-=20;

                break;

            case 's':
                break;

            default:
                ch='+';
                break;
        }

        if ( r==lines&&ch=='+' )
        {   ch='-';
            r-=20;
            continue;
        }
    }
    while ( ch == '+'||ch=='-' );
}



