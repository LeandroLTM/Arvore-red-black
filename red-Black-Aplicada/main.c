#include <stdio.h>
#include <stdlib.h>
#include "red-black.h"

int main()
{
    No *temp;
    Arvore *a;
    char opt = 1;
    char n[12];
    int aux ;

    a = criar_arvore();

    FILE *f;

    f = fopen("RedArquivo.txt","r");

    int fimArquivo;
    char chaveArquivo[11];
    No *tempArq;
    while(1){
        fimArquivo = fscanf(f,"%s",&chaveArquivo);
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
        printf("2 listar CPFs : \t\n");
        printf("3 Imprimir Arvore : \t\n");
        printf("4 Consultar: \t\n");
        printf("5 Sair e Arquivar: \t\n");

        scanf("%s",&opt);

        switch(opt) {
        case '1':
            printf("Informe o número: ");
            scanf("%s",&n);
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
                aux = 0;
                in_order_walk_listar(a->raiz,&aux);
            }else{
                printf("Nao existem CPFs cadastrados");
            }
            break;
        case '3':
            if(a->raiz != NULL) {
                aux = 0;
                pre_order_walk(a->raiz,aux);
            }else{
                printf("Árvore sem raiz!\n");
            }
            break;
        case '4':
            printf("Digite o CPF: ");
            scanf("%s",&n,aux);
            aux =0;
            if(buscar(a->raiz,n,&aux)){
                printf("CPF: %s\n Altura do Arvore: %d\n",n,aux);
            }else{
                printf("CPF nao encontrado \n Altura do Arvore: %d\n",aux);
            }
            break;
        case '5':
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
