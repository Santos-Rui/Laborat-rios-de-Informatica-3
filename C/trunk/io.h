#ifndef IO_H
#define IO_H

#define FILE_PRODUCT 1
#define FILE_CLIENT 2
#define FILE_SALES 3
#define MAXBUFF 32
int readFiles ( void * PRODUCT_CAT  ,void * CLIENT_CAT, void * ACCOUNTING, void * SALES, int type_selection, int max_buff, char *nomefich, int *validated );
void free_buffered_strings ( char **buff, int totalRead );
char **malloc_buffered_strings ( int totalRead, int max_buff );


void navigation( char **, int);
int main_menu();

#endif
