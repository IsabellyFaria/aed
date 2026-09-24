#include <stdio.h>
#include <stdlib.h>
//gcc 196413_lab5.c -o ex5

//Structs utilizadas
typedef struct Operacao{
    char tipo;
    char caractere;
    int posição;
    struct Operacao *prox;
}Operacao;
typedef struct Texto{
    char caractere;
    struct Texto *prox;
}Texto;
typedef struct Editor{
    Operacao *undo_list;
    Operacao *redo_list;
    int n_caracteres;
    Texto *tex;
}Editor;

//FUNÇÕES DE PILHA
    //pop
void pop_list(Operacao *cabeca){
    Operacao *velho = cabeca;
    cabeca = cabeca->prox;
    free(velho);
}

    //push
void push_list(Operacao *novo, Operacao *cabeca){
    novo->prox = cabeca;
    cabeca = novo;
}



//INICIALIZAÇÃO

    //Incialização de Editor
Editor incializa_editor(){
    Editor e;
    e.undo_list = NULL;
    e.redo_list = NULL;
    e.n_caracteres = 0;
    e.tex = NULL;
    return e;
}

//INSERIR 
    //Inserção na lista tex
void inserir_texto(char c, int posicao, Texto* lista){
    Texto *novo = malloc(sizeof(Texto));
    novo->caractere = c;
    if(lista == NULL){
        lista = novo;
        return;
    }
    int i = 0;
    Texto *aux = lista;
    while(i != posicao && aux->prox != NULL){
        aux = aux->prox;
        i++;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
}

    //Função principal
void inserir(){}
