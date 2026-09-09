#include <stdio.h>
#include <stdlib.h>

struct no {
int info; 
struct no *prox; 
};
typedef struct no No;
struct cx {
No **caixa;
int N; 
};
typedef struct cx Caixa;

No* incializa(){
    No* i;
    i->prox = NULL;
    return i;
}

No* aloca_caixas(int n){
    Caixa *lista;
    lista-> N = n;
    lista->caixa = malloc(n*sizeof(No));
    for(int i = 0; i < n; i++){
        lista->caixa[i] = incializa();
    }
    return lista;
}

int h(int item, int N){
    return (item%N);
}

void insere(Caixa *c, int item){
    int n = h(item, c->N);
    No novo = incializa();
    novo.info = item;
    novo.prox = c->caixa[1];
    c->caixa[0].prox = no;
}

void remove(Caixa *c, int item){
    int n = h(item, c->N);
    No *lista = c->caixas[n];
    No *ant = NULL;
    No *i = lista.prox;
    while(i != NULL){
        if(i.info == item){
            ant.prox = i.prox;
            free(i);
            break;
        }
        *ant = i;
        *i = i.prox;
    }
}

void desaloca_lista(No *cabeca){
    
    No *item = cabeca;
    while(item != Null){
        No *ant = item;
        item = item.prox;
        free(item);
    }
    
}

void desaloca_caixas(Caixa *c){
    int n = c->N;
    for(int i = 0; i < n; i++){
        desaloca_lista(c->caixas[i]);
    }
    free(c);
}

void imprime(Caixa *c){
    int n = c->N;
    for(int i = 0; i < n; i++){
        int j = c->caixas[i];
        while(j != NULL){
            printf(" %d ",j.info);
            j= j.prox;
        }
        printf("\n");
    }
}
