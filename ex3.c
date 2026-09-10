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
No* incializa()
{ 
    No *i = NULL; 
    return i;
} 
Caixa* aloca_caixas(int n){
    Caixa *lista = malloc(1 * sizeof(Caixa));
    lista->N = n; 
    lista->caixa = malloc(sizeof(No*)); 
    for(int i = 0; i < n; i++)
    { 
        lista->caixa[i] = incializa();
    } 
    return lista; 
} 
int h(int item, int N){
    return (item%N); 
} 
void insere(Caixa *c, int item){ 
    int n = h(item, c->N); 
    No novo;
    novo.info = item; 
    if(c->caixa[n] == NULL){ 
        c->caixa[n] = &novo; 
        novo.prox = NULL;
    }else{ 
        novo.prox = c->caixa[n];
        c->caixa[n] = &novo;
    } 
    printf("\n %d %d %d", n, novo.info, novo.prox->info); 
} 
void retira(Caixa *c, int item){ 
    int n = h(item, c->N); No *lista = c->caixa[n]; 
    No *ant = NULL; No *i = lista->prox;
    while(i != NULL){ 
        if(i->info == item){
            ant->prox = i->prox; free(i); break; 
        } 
        ant = i;i = i->prox; 
    } 
} 
void desaloca_lista(No *cabeca){ 
    No *item = cabeca; 
    while(item != NULL){ 
        No *ant = item; item = item->prox; free(item); 
    } 
} 
void desaloca_caixas(Caixa *c){ 
    int n = c->N; 
    for(int i = 0; i < n; i++){ 
        desaloca_lista(c->caixa[i]); 
    }
    free(c); 
} void imprime(Caixa *c){ 
    int n = c->N; 
    for(int i = 0; i < n; i++){ 
        No *j = c->caixa[i]; 
        while(j != NULL){ 
            printf(" %d ",j->info); 
            j= j->prox; 
        } 
        printf("\n"); 
        free(j); 
    } 
} 
int main(){
     int N; 
     scanf("%d", &N); 
     Caixa *lista = aloca_caixas(N);
     int m; scanf("%d", &m); 
     for(int i = 0; i<m; i++){ 
        int num; scanf("%d", &num);
        insere(lista, num); 
    } 
    //imprime(lista); 
    desaloca_caixas(lista); return 0; 
}