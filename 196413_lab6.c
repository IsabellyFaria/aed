#include <stdio.h>
#include <stdlib.h>

typedef struct Tarefa {
    int ID;
    int n_pg;
    char prioridade;
    struct Tarefa* ant;
    struct Tarefa* prox;
} Tarefa;

void imprimir_tarefa(Tarefa* tarefa) {
    if (tarefa != NULL) {
        printf("%d %d %c\n", tarefa->ID, tarefa->n_pg, tarefa->prioridade);
    }
}

void processar_tarefa(Tarefa** lista) {
    if (lista == NULL || *lista == NULL) {
        printf("\n"); 
        return;
    }
    Tarefa* aux = *lista;
    imprimir_tarefa(aux);
    
    *lista = aux->prox;
    if (*lista != NULL) {
        (*lista)->ant = NULL;
    }
    free(aux);
}

void cancelar_tarefa(Tarefa** lista, int ind) {
    if (lista == NULL || *lista == NULL) {
        printf("\n"); 
        return;
    }
    
    Tarefa* aux = *lista;
    for (int i = 0; i < ind && aux != NULL; i++) {
        aux = aux->prox;
    }
    
    if (aux == NULL) {
        printf("\n");
        return;
    }
    
    imprimir_tarefa(aux);

    if (aux->ant != NULL) {
        aux->ant->prox = aux->prox;
    } else {
        *lista = aux->prox;
    }

    if (aux->prox != NULL) {
        aux->prox->ant = aux->ant;
    }

    free(aux);
}

void exibir_lista(Tarefa* lista, int ordem) {
    if (lista == NULL) {
        return;
    }
    imprimir_tarefa(lista);
    if (ordem == 0) {
        exibir_lista(lista->prox, ordem);
    } else {
        exibir_lista(lista->ant, ordem);
    }
}

void adicionar_tarefa(Tarefa** lista, int id, int n, char prioridade) {
    Tarefa* nova = malloc(sizeof(Tarefa));
    nova->ID = id;
    nova->n_pg = n;
    nova->prioridade = prioridade;
    nova->ant = NULL;
    nova->prox = NULL;

    if (*lista == NULL) {
        *lista = nova;
        return;
    }

    if (prioridade == 'U') {
        if ((*lista)->prioridade != 'U') {
            nova->prox = *lista;
            (*lista)->ant = nova;
            *lista = nova;
        } else {
            Tarefa* aux = *lista;
            while (aux->prox != NULL && aux->prox->prioridade == 'U') {
                aux = aux->prox;
            }
            
            nova->prox = aux->prox;
            nova->ant = aux;
            if (aux->prox != NULL) {
                aux->prox->ant = nova;
            }
            aux->prox = nova;
        }
    } else {
        Tarefa* aux = *lista;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = nova;
        nova->ant = aux;
    }
}

void liberar_lista(Tarefa** lista) {
    if (lista == NULL || *lista == NULL) {
        return;
    }
    
    Tarefa* atual = *lista;
    Tarefa* prox_no = NULL;
    
    while (atual != NULL) {
        prox_no = atual->prox;
        free(atual);
        atual = prox_no;
    }
    
    *lista = NULL; 
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    Tarefa* lista = NULL;

    for (int i = 0; i < n; i++) {
        char ent;
        scanf(" %c", &ent); 

        switch (ent) {
            case 'P':
                processar_tarefa(&lista);
                break;
            case 'C': {
                int ind;
                scanf("%d", &ind);
                cancelar_tarefa(&lista, ind);
                break;
            }
            case 'E': {
                int ordem;
                scanf("%d", &ordem);
                Tarefa* aux = lista;
                if (aux == NULL) {
                    printf("\n"); 
                    break;
                }
                if (ordem == 1) {
                    while (aux->prox != NULL) {
                        aux = aux->prox;
                    }
                }
                exibir_lista(aux, ordem);
                break;
            }
            case 'A': {
                int id, n_pg;
                char prioridade;
                scanf("%d %d %c", &id, &n_pg, &prioridade);
                adicionar_tarefa(&lista, id, n_pg, prioridade);
                break;
            }
        }
    }
    liberar_lista(&lista);
    return 0;
}