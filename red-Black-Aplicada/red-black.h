#ifndef RED-BLACK_H_INCLUDED
#define RED-BLACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct no {
    struct no *esquerda;
    struct no *direita;
    struct no *pai;
    char CPF[12];
    char cor;
} No;

typedef struct arvore {
    No *raiz;
}Arvore;

Arvore *criar_arvore();

No *criar_no(char *CPF);

void inserir(Arvore *a, No *r,No *n);

void pre_order_walk(No *n, int aux);

void pre_order_walkEscrever(No *n,FILE *f);

void rotate_ll(Arvore *a,No *n);

int cmpCPF(char *cpf1,char *cpf2);

int buscar(No *r, char *n,int *auxAut);

void in_order_walk_listar(No *n, int *aux);


#endif // RED-BLACK_H_INCLUDED
