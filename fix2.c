#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int qtd;
    int tam;
    int *dados;
}Lista;

void alocar_vetor(Lista *l, int tam){

    l->dados = calloc(tam, sizeof(int));
    l->tam = tam;
}

int insere(Lista *l, int item, int posicao){
    if(posicao<l->tam || l->qtd != l->tam){
        for(int i = l->qtd; i>posicao; i--){
            l->dados[i] = l->dados[i-1];  
        }
        l->dados[posicao] = item;
        l->qtd++;
        return 1;
    }
    return 0;
}

int main(){
    int tam = 4;
    Lista l;
    alocar_vetor(&l,tam);
    
    for(int i = 0; i < tam; i++){
        insere(&l, i, 0);
    }
    for(int i = 0; i < tam; i++){
        printf("\n%d", l.dados[i]);
    }
    
    return 0;
}