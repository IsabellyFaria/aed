#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int simbolo;
	struct No	*prox;
	struct No *ant;	
}No;

typedef struct Tambor{
	No *cabeca;	
}Tambor;

typedef struct Maquina{
	int n_tambores;
	Tambor *tambores;	
}Maquina;

Maquina *cria_maquina(int N){
	Maquina *m;
	m = malloc(sizeof(Maquina));
	m->tambores = malloc(N * sizeof(Tambor));
	m->n_tambores = N;
	for(int i = 0; i < N; i++){
		m->tambores[i].cabeca = NULL;
	}
	return m;
}

void insere_simbolo(Tambor *t, int s){
	No *novo;
	novo = malloc(sizeof(No));
	novo->simbolo = s;
	if(t->cabeca == NULL){
			novo->prox = novo;
		    novo->ant = novo;
		    t->cabeca = novo;
	}else{
		No *aux = t->cabeca;
		while(aux->prox != t->cabeca){
		    aux = aux->prox;
		}
		novo->prox = t->cabeca;
		aux->prox = novo;
		novo->ant = aux;
		t->cabeca->ant = novo;
	}
}

void remove_simbolo(Tambor *t, int s){
	No* i = t->cabeca;
	do{
		if(i->simbolo == s){
			i->ant->prox = i->prox;
			i->prox->ant = i->ant;
			if(i == t->cabeca){
				t->cabeca = i->prox;	
			}
			free(i);
			break;
		}
		i = i->prox;
		}while(i != t->cabeca);
}

void desaloca_tambor(Tambor *t){
    if(t == NULL) return;
    if(t->cabeca != NULL){
       No *i = t->cabeca->prox;
    	while(i != t->cabeca){
    		No *aux = i;
    		i = i->prox;
    		free(aux);
    	}
    	free(t->cabeca); 
    }
}
void desaloca_caixas(Maquina *m){
	int n = m->n_tambores;
	for(int i = 0; i<n; i++){
			desaloca_tambor(&m->tambores[i]);
	}
	free(m->tambores);
	free(m);
}

int rotaciona(Tambor *t, int rotacao, int direcao){
    No* aux = t->cabeca;
    for(int i = 0; i<rotacao; i++){
        if(direcao == 1){
            aux = aux->ant;
        }else{
            aux = aux->prox;
        }
    }
    return aux->simbolo;
}
int main()
{
		int n, m;
		scanf("%d",&n);
		scanf("%d",&m);
		Maquina *ma = cria_maquina(n);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				int x;
				scanf("%d", &x);
				insere_simbolo(&ma->tambores[i], x);
			}
		}
		int rot[n], dir[n], rem[n];
		for(int i = 0; i<n;i++){
		    scanf("%d", &rot[i]);
		}
		for(int i = 0; i<n;i++){
		    scanf("%d", &dir[i]);
		}
		for(int i = 0; i<n;i++){
		    scanf("%d", &rem[i]);
		}
		printf("-");
	    for(int i = 0; i < n; i++){
	        printf("%d-", rotaciona(&ma->tambores[i], rot[i], dir[i]));
	    }
	    printf("\n-");
	     for(int i = 0; i < n; i++){
	        remove_simbolo(&ma->tambores[i], rem[i]);
	        printf("%d-", rotaciona(&ma->tambores[i], rot[i], dir[i]));
	    }
	    desaloca_caixas(ma);
}