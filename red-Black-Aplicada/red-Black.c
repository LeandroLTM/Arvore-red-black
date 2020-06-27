#include "red-black.h"

Arvore *criar_arvore() {
    Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));

    arvore->raiz = NULL;

    return arvore;
}

No *criar_no(char *CPF){
    No *n = (No *)malloc(sizeof(No));

    strcpy(n->CPF,CPF);
    n->cor = 'r';
    n->pai = NULL;
    n->esquerda = NULL;
    n->direita = NULL;
}

void inserir(Arvore *a,No *r,No *n) {
    int aux = cmpCPF(n->CPF,r->CPF);
    if(aux == -1) {
        if(r->esquerda == NULL) {
            r->esquerda = n;
            n->pai = r;
        }else{
            inserir(a,r->esquerda,n);
        }

    }else{
        if(r->direita == NULL){
            r->direita = n;
            n->pai = r;
        }else{
            inserir(a,r->direita,n);
        }
    }
    recolorir(a,n);
}

int cor_no(No *n) {
    return n == NULL ? 'b' : n->cor;
}

void recolorir(Arvore *a,No *n){
    if(a->raiz != n && n != NULL){
        No *pai = n->pai;
        No *vo = n->pai->pai;
        No *tio = NULL;

        if(vo != NULL){
            tio = vo->direita == pai ? vo->esquerda : vo->direita;
        }

        if(n->cor == 'r' && pai->cor == 'r' && cor_no(tio) == 'r'){
            tio->cor = 'b';
            pai->cor = 'b';
            vo->cor = 'r';

        }

        if(n->cor == 'r' && pai->cor == 'r' && cor_no(tio) == 'b'){
            if(vo->direita == pai && pai->direita == n){
                rotate_ll(a,pai);
                n->pai->cor = 'b';
                n->pai->esquerda->cor = 'r';
            }else if(vo->esquerda == pai && pai->esquerda == n){
                rotate_rr(a,pai);
                n->pai->cor = 'b';
                n->pai->direita->cor = 'r';
            }else if(vo->direita == pai && pai->esquerda == n){
                rotate_rr(a,n);
                rotate_ll(a,vo->direita);
                n->cor = 'b';
                n->esquerda->cor = 'r';
                n->direita->cor = 'r';
            }else if(vo->esquerda == pai && pai->direita == n){
                rotate_ll(a,n);
                rotate_rr(a,vo->esquerda);
                n->cor = 'b';
                n->esquerda->cor = 'r';
                n->direita->cor = 'r';
            }
        }
        recolorir(a,n->pai);
    }else if(n != NULL){
        n->cor = 'b';
    }

}

void rotate_rr(Arvore *a,No *n) {
    No *tmp_direita = n->direita;
    No *pai = n->pai;
    No *vo = n->pai->pai;

    if(vo != NULL){
            if(vo->esquerda == pai){
                vo->esquerda = n;
            }else{
                vo->direita = n;
            }
    }

    n->direita = n->pai;
    n->pai = n->pai->pai;
    n->direita->pai = n;
    n->direita->esquerda = tmp_direita;

    if(pai->esquerda != NULL){
            pai->esquerda->pai = pai;
    }

    if(a->raiz == n->direita) {
        a->raiz = n;
    }
}

void rotate_ll(Arvore *a,No *n) {
    No *tmp_esquerda = n->esquerda;
    No *pai = n->pai;
    No *vo = n->pai->pai;

    if(vo != NULL){
            if(vo->esquerda == pai){
                vo->esquerda = n;
            }else{
                vo->direita = n;
            }
    }

    n->esquerda = n->pai;
    n->pai = n->pai->pai;
    n->esquerda->pai = n;
    n->esquerda->direita = tmp_esquerda;

    if(pai->direita != NULL){
            pai->direita->pai = pai;
    }

    if(a->raiz == n->esquerda) {
        a->raiz = n;
    }
}

void pre_order_walk(No *n, int aux) {
    if(n!=NULL) {
        printf("%s (%c) Altura: %d\n",n->CPF,n->cor,aux);
        aux++;
        pre_order_walk(n->esquerda,aux);
        pre_order_walk(n->direita,aux);
    }
}

void pre_order_walkEscrever(No *n,FILE *f){
    if(n!=NULL) {
        fprintf(f,"%s\n",n->CPF);
        pre_order_walkEscrever(n->esquerda,f);
        pre_order_walkEscrever(n->direita,f);
    }
}

void in_order_walk_listar(No *n, int *aux){
    if(n!=NULL) {
        in_order_walk_listar(n->esquerda,aux);
        *aux += 1;
        printf("%d:\t %s\n",*aux,n->CPF);
        in_order_walk_listar(n->direita,aux);
    }
}

int cmpCPF(char *cpf1,char *cpf2){

    for(int i=0;i<11;i++){
        if(cpf1[i] < cpf2[i]){
            return -1;
        }else if(cpf1[i] > cpf2[i]){
            return 1;
        }
    }
    return 0;

}

int buscar(No *r, char *n,int *auxAut){
    int aux = cmpCPF(n,r->CPF);
    if(aux == -1 && r->esquerda != NULL) {
        *auxAut += 1;
        buscar(r->esquerda,n,auxAut);
    }else if(aux == 1 && r->direita != NULL){
        *auxAut += 1;
        buscar(r->direita,n,auxAut);
    }else if(aux == 0){
        return 1;
    }else{
        return 0;
    }
}

