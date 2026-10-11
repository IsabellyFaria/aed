#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no* prox;
    struct no* ant;
}No;
typedef struct Lista{
    No* cabeca;
}Lista;

void inicializa(Lista *l){
    l->cabeca = NULL;
}
No *criarNo(int valor){
    No* novo= malloc(sizeof(No));
    novo->valor = valor;
    return novo;
}

void inserir(Lista *l, No* novo, int posicao){
    if(posicao == 0){
        novo->ant = NULL;
        novo->prox = l->cabeca;
        l->cabeca->ant = novo;
        l->cabeca = novo;
        return;
    }
    if(l->cabeca == NULL){

    }
    No* aux = l->cabeca;
    int i = 0;
    while(i<posicao-1 && aux->prox != NULL){
        aux = aux->prox;
        i++;
    }
    novo->prox = aux->prox;
    novo->ant = aux;
    aux->prox = novo;
}
void remover(Lista *l, No* velho){
    if(velho == l->cabeca){
        if(l->cabeca->prox != NULL){
          l->cabeca = l->cabeca->prox;
            l->cabeca->ant = NULL;  
        }
        else{
            l->cabeca = NULL;
        }
        free(velho);
        return;
    }
    No *aux = l->cabeca;
    while(aux->prox != velho){
        aux = aux->prox;
    }
    aux->prox = velho->prox;
    if(aux->prox != NULL){
        aux->prox->ant = aux;
    }
    
    free(velho);
}
No *buscaNo(Lista *l, int valor){
    No* aux = l->cabeca;
    while(aux != NULL && aux->valor != valor){
        aux = aux->prox;
    }
    return aux;
    
}

void desalocar(Lista *l){
    No* i = l->cabeca;
    while(i != NULL){
        No* aux = i;
        i = i->prox;
        free(aux);
    }
}
int main(){
    Lista list;
    inicializa(&list);
    int opcao, valor, indice;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar\n");
        printf("2. Remover\n");
        printf("3. Buscar o indice do valor\n");
        printf("4. Parar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                printf("Digite o indice/posicao do no a ser adicionado: ");
                scanf("%d", &indice);
                
                No* novo = criarNo(valor);
                if (novo != NULL) {
                    inserir(&list, novo, indice);
                    printf("Adicionado com sucesso!\n");
                } else {
                    printf("Erro ao alocar memoria.\n");
                }
                break;
            }
            case 2: {
                printf("Digite o valor do no a ser removido: ");
                scanf("%d", &valor);
                
                // Busca o nó pelo valor para poder passá-lo para a função remover
                No* alvo = buscaNo(&list, valor);
                if (alvo != NULL) {
                    remover(&list, alvo);
                    printf("Operacao de remocao executada.\n");
                } else {
                    printf("Erro: Valor nao encontrado na lista.\n");
                }
                break;
            }
            case 3: {
                printf("Digite o valor que deseja buscar: ");
                scanf("%d", &valor);
                
                No* encontrado = buscaNo(&list, valor);
                if (encontrado != NULL) {
                    No* aux = list.cabeca;
                    int idx = 0;
                    while (aux != encontrado) {
                        aux = aux->prox;
                        idx++;
                    }
                    printf("Valor encontrado no indice: %d\n", idx);
                } else {
                    printf("Valor nao encontrado na lista.\n");
                }
                break;
            }
            case 4:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    desalocar(&list);
    return 0;
}