#include <stdio.h>

#define tamanho 500
typedef struct no{
    int valor;
}No;
typedef struct lista{
    No l[tamanho];
    int nElementos;
}Lista;
void incializa(Lista* a){
    a->nElementos = 0;
}
int inserir(Lista* l,int indice, int valor){
    if(l->nElementos == tamanho){
        return 0;
    }
    for(int i = l->nElementos; i > indice; i--){
        l->l[i] = l->l[i-1]; 
    }
    l->l[indice].valor = valor; 
    l->nElementos++;
    return 1;
}

void remover(Lista* l, int indice){
    for(int i = indice+1; i < l->nElementos; i++){
        l->l[i-1] = l->l[i]; 
    }
    l->nElementos--;
}

int busca(Lista* l,int valor){
    for(int i = 0; i <l->nElementos; i++){
        if(l->l[i].valor == valor){
            return i;
        }
    }
    return -1;
}

int main() {
    Lista list;
    incializa(&list);
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
            case 1:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &valor);
                printf("Digite o indice do no a ser adcionado: ");
                scanf("%d", &indice);
                if (inserir(&list, indice, valor)) {
                    printf("Adicionado com sucesso!\n");
                } else {
                    printf("Erro: espaco insuficiente.\n");
                }
                break;

            case 2:
                printf("Digite o indice do no a ser removido: ");
                scanf("%d", &indice);
                remover(&list, indice);
                printf("Operacao de remocao executada.\n");
                break;

            case 3:
                printf("Digite o valor que deseja buscar: ");
                scanf("%d", &valor);
                indice = busca(&list,valor);
                if (indice != -1) {
                    printf("Valor encontrado no indice: %d\n", indice);
                } else {
                    printf("Valor nao encontrado na lista.\n");
                }
                break;

            case 4:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}