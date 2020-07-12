#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "accounting.h"
#define MAXSTR 32



void sub_menuCC(CL_CAT_T cc){
    int control=1;
    int selection;
    char c;
    char prefix;
    STRING_ARRAY_T lista;


    while (control==1) {
        printf("\033[1;1H\033[2J");
        printf("_____________________________________\n");
        printf("|                                    |\n");
        printf("|         Catálogo de Clientes       |\n");
        printf("|                                    |\n");
        printf("|------------------------------------|\n");
        printf("|                                    |\n");
        printf("|  1 —                               |\n");
        printf("|  2 — Procurar por letra            |\n");
        printf("|  3 —                               |\n");
        printf("|  4 —                               |\n");
        printf("|  5 - Voltar                        |\n");
        printf("|____________________________________|\n");

        if (scanf("%d",&selection)!=1)
            selection=8;

        switch(selection) {
            case 1 :
                break;

            case 2 :
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf ("Que letra deseja procurar?\n");
                if (scanf ("%c",&prefix) ){}
                if(prefix >= 'a' && prefix <= 'z') /*passar a maiscula*/
                    prefix= prefix - 'a' + 'A'; 
                if (prefix >= 'A' && prefix <= 'Z'){
                    lista = CLIENT_CAT_getKeysBegginingWithChar( cc, prefix);
                    navigation((char**)STRING_ARRAY_getStringArrayPointer(lista),STRING_ARRAY_getNumElems(lista));
                    }

                else{
                    printf("\033[1;1H\033[2J");
                    while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                    printf("Caracter inválido\n\nEnter para continuar...\n");
                    getchar();
                    }
                break;
                

            case 3 :
                break;

            case 4 :
                break;

            case 5:
                control = 0;
                break;

            default:
                printf("\033[1;1H\033[2J");
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf("Comando inválido\n\nEnter para continuar...\n");
                getchar();
                break;
        }


    }
}

void sub_menuCP(PR_CAT_T cp){
    int control=1;
    int selection;
    char c;
    char prefix;
    STRING_ARRAY_T lista;

    while (control==1) {
        printf("\033[1;1H\033[2J");
        printf("_____________________________________\n");
        printf("|                                    |\n");
        printf("|        Catalogo de Produtos        |\n");
        printf("|                                    |\n");
        printf("|------------------------------------|\n");
        printf("|                                    |\n");
        printf("|  1 —                               |\n");
        printf("|  2 — Procurar por letra            |\n");
        printf("|  3 —                               |\n");
        printf("|  4 —                               |\n");
        printf("|  5 - Voltar                        |\n");
        printf("|____________________________________|\n");

        if (scanf("%d",&selection)!=1)
            selection=8;

        switch(selection) {
            case 1 :
                break;

            case 2 :
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf ("Que letra deseja procurar?\n");
                if (scanf ("%c",&prefix) ){}
                if(prefix >= 'a' && prefix <= 'z') /*passar a maiscula*/
                    prefix= prefix - 'a' + 'A'; 
                if (prefix >= 'A' && prefix <= 'Z'){
                    lista = PRODUCT_CAT_getKeysBegginingWithChar( cp, prefix);
                    navigation((char**)STRING_ARRAY_getStringArrayPointer(lista),STRING_ARRAY_getNumElems(lista));
                    }

                else{
                    printf("\033[1;1H\033[2J");
                    while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                    printf("Caracter inválido\n\nEnter para continuar...\n");
                    getchar();
                    }
                break;

            case 3 :
                break;

            case 4 :
                break;

            case 5:
                control = 0;
                break;

            default:
                printf("\033[1;1H\033[2J");
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf("Comando inválido\n\nEnter para continuar...\n");
                getchar();
                break;
        }


    }

}
void sub_menuComp( PURCHASES_T comp ){
    int control=1;
    int selection;
    int mes;
    char c;
    char key[MAXSTR];
    STRING_ARRAY_T lista;

    while (control==1) {
        printf("\033[1;1H\033[2J");
        printf("_____________________________________\n");
        printf("|                                    |\n");
        printf("|          Módulo de Compras         |\n");
        printf("|                                    |\n");
        printf("|------------------------------------|\n");
        printf("|                                    |\n");
        printf("|  1 —                               |\n");
        printf("|  2 —                               |\n");
        printf("|  3 —  Q9                           |\n");
        printf("|  4 —  Q10                          |\n");
        printf("|  5 - Voltar                        |\n");
        printf("|____________________________________|\n");
        if (scanf("%d",&selection)!=1)
            selection=8;

        switch(selection) {
            case 1 :
                break;

            case 2 :
                 break;

            case 3 :
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf ("Que cliente deseja procurar?\n");
                if (scanf ("%s",key) ){}
                
                printf ("Que mes deseja procurar?\n");
                if (scanf ("%d",&mes) ){}
                lista= PURCHASES_getClientMostBoughtProductListByMonthDesc(comp,key,mes);
                if(lista)
                    if(STRING_ARRAY_getNumElems(lista)!=0)
                        navigation ( (char**)STRING_ARRAY_getStringArrayPointer(lista) , STRING_ARRAY_getNumElems(lista) );
                break;

            case 4 :
                lista = PURCHASES_getClientListAllMonth(comp);
                navigation((char**)STRING_ARRAY_getStringArrayPointer(lista),STRING_ARRAY_getNumElems(lista));
                break;

            case 5:
                control = 0;
                break;

            default:
                printf("\033[1;1H\033[2J");
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf("Comando inválido\n\nEnter para continuar...\n");
                getchar();
                break;
        }


    }

}
void sub_menuCont( ACCOUNTING_T cont ){
    int control=1;
    int selection;
    char c;
    char key[MAXSTR];
    int mes,mes1,mes2,totalcompras;
    int quantN, quantP;
    float billedinterval;
    STRING_ARRAY_T lista;

    while (control==1) {
    	printf("\033[1;1H\033[2J");
        printf("_____________________________________\n");
        printf("|                                    |\n");
        printf("|           Contabilidade            |\n");
        printf("|                                    |\n");
        printf("|------------------------------------|\n");
        printf("|                                    |\n");
        printf("|  1 —                               |\n");
        printf("|  2 — Q3 Prod e Mes -> N P e Total  |\n");
        printf("|  3 — Q4 Produtos nunca comprados   |\n");
        printf("|  4 — Q7 Facturaçao e vendas x...y  |\n");
        printf("|  5 - Voltar                        |\n");
        printf("|____________________________________|\n");

        if (scanf("%d",&selection)!=1)
            selection=8;

        switch(selection) {
            case 1 :
                break;

            case 2 :
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf ("Que Produto deseja procurar?\n");
                if (scanf ("%s",key) ){}
                printf ("Que mes deseja procurar?\n");
                if (scanf ("%d",&mes) ){}
                quantN = ACCOUNTING_getTotalQuantityInMonthByType(cont,key,mes,'n');
                quantP = ACCOUNTING_getTotalQuantityInMonthByType(cont,key,mes,'p');
                printf ("Total comprado = %d\nTotal em N:%d\n Total em P : %d\n",quantN+quantP,quantN,quantP);
                printf("\n\nEnter para continuar...\n");
                getchar();
                getchar();
                 break;

            case 3 :
                
                lista =  ACCOUNTING_getNonBilledProducts(cont);
                navigation((char**)STRING_ARRAY_getStringArrayPointer(lista),STRING_ARRAY_getNumElems(lista));
                break;

            case 4 :
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf ("Que intervalo de meses (separado por espaços)?\n");
                if( scanf("%d %d",&mes1,&mes2)){}
                billedinterval = ACCOUNTING_getTotalBilledInMonthInterval ( cont ,mes1,mes2); 
                totalcompras= ACCOUNTING_totalBoughtInMonthInterval(cont ,mes1,mes2); /*este numero esta mt alto*/
                printf("Total de compras realizadas : %d \nTotal facturado: %f \n", totalcompras,billedinterval);
                printf("\n\nEnter para continuar...\n");
                getchar();
                getchar();
                break;

            case 5:
                control = 0;
                break;

            default:
                printf("\033[1;1H\033[2J");
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf("Comando inválido\n\nEnter para continuar...\n");
                getchar();
                break;
        }


    }

}
int main_menu(CL_CAT_T cc, PR_CAT_T cp, ACCOUNTING_T cont, PURCHASES_T comp  ) {
    int selection;
    int control=1;
    char c;

    while (control==1) {

        printf("\033[1;1H\033[2J");
        printf("_____________________________________\n");
        printf("|                                    |\n");
        printf("| Escolha o Módulo que pretende usar |\n");
        printf("|                                    |\n");
        printf("|------------------------------------|\n");
        printf("|                                    |\n");
        printf("|  1 — Catálogo de clientes          |\n");
        printf("|  2 — Catálogo de produtos          |\n");
        printf("|  3 — Módulo de compras             |\n");
        printf("|  4 — Contabilidade                 |\n");
        printf("|  5 - Sair                          |\n");
        printf("|____________________________________|\n");


        if (scanf("%d",&selection)!=1)
            selection=8;

        switch(selection) {
            case 1 :
                sub_menuCC(cc);
                break;

            case 2 :
                sub_menuCP(cp);
                 break;

            case 3 :
                sub_menuComp(comp);
                break;

            case 4 :
                sub_menuCont(cont);
                break;


            case 5:
                control = 0;
                break;

            default:
                printf("\033[1;1H\033[2J");
                while ((c = getchar()) != '\n' && c != EOF);  /*limpar stdin*/
                printf("Comando inválido\n\nEnter para continuar...\n");
                getchar();
                break;
        }


    }

    return 0;
}
