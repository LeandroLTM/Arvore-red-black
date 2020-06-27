#ifndef RED-BLACK_H_INCLUDED
#define RED-BLACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct no {
    struct no *esquerda;
    struct no *direita;
    struct no *pai;
    int chave;
    char cor;
} No;

typedef struct arvore {
    No *raiz;
}Arvore;

Arvore *criar_arvore();

No *criar_no(int chave);

void inserir(Arvore *a, No *r,No *n);

void in_order_walk(No *n);

void pre_order_walkEscrever(No *n,FILE *f);

void rotate_ll(Arvore *a,No *n);


#endif // RED-BLACK_H_INCLUDED
