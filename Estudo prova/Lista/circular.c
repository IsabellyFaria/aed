#include <stdio.h>
#include <stdlib.h>
typedef struct no{
    int valor;
    struct no* prox;
}No;
typedef struct Lista{
    No* cabeca;
    No* cauda;
}Lista;

void inicializa(Lista *l){
    l->cabeca = NULL;
    l->cauda = NULL;
}
No *criarNo(int valor){
    No* novo= malloc(sizeof(No));
    novo->valor = valor;
    return novo;
}

void inserir(Lista *l, No* novo){
    if(l->cabeca == NULL){
        l->cabeca = novo;
        l->cabeca->prox = l->cabeca;
        l->cauda = l->cabeca;
        return;
    }
    novo->prox = l->cabeca;
    l->cauda->prox = novo;
    l->cabeca = novo;
}
void remover(Lista *l, No* velho){
    No* aux = l->cabeca;
    if(l->cabeca == velho){
        if(l->cabeca->prox == l->cabeca){
            l->cabeca == NULL;
            free(velho);
            return;
        }else{
            l->cabeca = l->cabeca->prox;
            l->cauda->prox = l->cabeca;
        }
    }else{
        while(aux->prox != velho){
            aux = aux->prox;
        }
        aux->prox = velho->prox;
    }
    free(velho);
}
No *buscaNo(Lista *l, int valor){
    if(l->cabeca == NULL){
        return NULL;
    }
    if(l->cabeca->valor == valor){
        return l->cabeca;
    }
    No* aux = l->cabeca->prox;
    while(aux != l->cabeca){
        if(aux->valor == valor){
            return aux;
        }
        aux = aux->prox;
    }
    return  NULL;
    
}

void desalocar(Lista *l){
    No* i = l->cabeca->prox;
    while(i != l->cabeca){
        No* aux = i;
        i = i->prox;
        free(aux);
    }
    free(i);
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
                
                
                No* novo = criarNo(valor);
                if (novo != NULL) {
                    inserir(&list, novo);
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