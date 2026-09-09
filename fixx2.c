#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
    struct Lista *prox;
    int dado;
}Lista;

void insere(Lista **l, int valor){
    Lista *no = (Lista *)malloc(sizeof(Lista));
    no->prox = *l;
    no->dado = valor;
    *l = no;
}

int main(){
    int tam = 4;
    Lista *l = NULL;

    
    for(int i = 0; i < tam; i++){
        insere(&l, i);
    }
    
    
    Lista *atual = l;
    while(atual != NULL){
        printf("\n%d", atual->dado);
        atual = atual->prox;
    }
    
    // Liberar memória alocada
    while(l != NULL){
        Lista *temp = l;
        l = l->prox;
        free(temp);
    }
    return 0;
}