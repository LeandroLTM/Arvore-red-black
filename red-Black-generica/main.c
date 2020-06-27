#include <stdio.h>
#include <stdlib.h>
#include "red-black.h"

int main()
{
    No *temp;
    Arvore *a;
    char opt = 1;
    int n;

    a = criar_arvore();

    FILE *f;

    f = fopen("RedArquivo.txt","r");

    int fimArquivo, chaveArquivo;
    No *tempArq;
    while(1){
        fimArquivo = fscanf(f,"%d",&chaveArquivo);
        if(fimArquivo != 1) break;
        tempArq = criar_no(chaveArquivo);
        if(a->raiz == NULL) {
                a->raiz = tempArq;
                a->raiz->cor = 'b';
        }else{
                inserir(a,a->raiz,tempArq);
        }
    }

    fclose(f);

    while(opt) {

        printf("opcoes: \t\n");
        printf("1 inserir: \t\n");
        printf("2 ver : \t\n");
        printf("3 Sair e Arquivar: \t\n");

        scanf("%s",&opt);

        switch(opt) {
        case '1':
            printf("Informe o número: ");
            scanf("%d",&n);
            temp = criar_no(n);

            if(a->raiz == NULL) {
                a->raiz = temp;
                a->raiz->cor = 'b';
            }else{
                inserir(a,a->raiz,temp);
            }
            break;
        case '2':
            if(a->raiz != NULL) {
                in_order_walk(a->raiz);
            }else{
                printf("Árvore sem raiz!\n");
            }
            break;
        case '3':
            opt = 0;
            break;
        }
    }

    f = fopen("RedArquivo.txt","w");
    if(a->raiz != NULL) {
            pre_order_walkEscrever(a->raiz,f);
    }
    fclose(f);

    return 0;
}
