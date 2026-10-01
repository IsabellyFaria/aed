#include <stdio.h>
#include <stdlib.h>

// Structs utilizadas
    typedef struct Operacao {
        char tipo;  
        char caractere;   
        int posicao;      
        struct Operacao *prox;
    } Operacao;

    typedef struct Texto {
        char caractere;
        struct Texto *prox;
    } Texto;

    typedef struct Editor {
        Operacao *undo_list;
        Operacao *redo_list;
        int n_caracteres;
        Texto *tex;
    } Editor;

// INICIALIZAÇÃO
    Editor* inicializa_editor() {
        Editor* e = malloc(sizeof(Editor));
        e->undo_list = NULL;
        e->redo_list = NULL;
        e->n_caracteres = 0;
        e->tex = NULL;
        return e;
    }

// DESALOCAÇÃO
    void desaloca_operacao(Operacao* o) {
        Operacao* aux = o;
        while(aux != NULL) {
            Operacao* ant = aux;
            aux = aux->prox;
            free(ant);
        }
    }

    void desaloca_texto(Texto* t) {
        Texto* aux = t;
        while(aux != NULL) {
            Texto* ant = aux;
            aux = aux->prox;
            free(ant);
        }
    }

    void desaloca_editor(Editor* e) {
        if(e != NULL) {
            desaloca_texto(e->tex);
            desaloca_operacao(e->undo_list);
            desaloca_operacao(e->redo_list);
            free(e);
        }
    }

// INSERÇÃO NO TEXTO
    void inserir_texto(Editor* e, char c, int posicao) {
        Texto *novo = malloc(sizeof(Texto));
        novo->caractere = c;
        novo->prox = NULL;

        if(posicao == 0 || e->tex == NULL) {
            novo->prox = e->tex;
            e->tex = novo;
        } else {
            int i = 0;
            Texto *aux = e->tex;
            while(aux != NULL && i < posicao - 1) {
                aux = aux->prox;
                i++;
            }
            if(aux != NULL) {
                novo->prox = aux->prox;
                aux->prox = novo;
            } else {
                Texto *ant = NULL;
                aux = e->tex;
                while(aux != NULL) {
                    ant = aux;
                    aux = aux->prox;
                }
                if(ant != NULL) {
                    ant->prox = novo;
                }
            }
        }
        e->n_caracteres++;
    }

// REMOÇÃO DO TEXTO
    char remover_texto(Editor* e, int posicao) {
        if(e->tex == NULL || posicao < 0 || posicao >= e->n_caracteres) return '\0';

        Texto* aux = e->tex;
        char c;

        if(posicao == 0) {
            e->tex = aux->prox;
            c = aux->caractere;
            free(aux);
        } else {
            int i = 0;
            Texto* ant = NULL;
            while(aux != NULL && i < posicao) {
                ant = aux;
                aux = aux->prox;
                i++;
            }
            if(aux != NULL && ant != NULL) {
                ant->prox = aux->prox;
                c = aux->caractere;
                free(aux);
            } else {
                return '\0';
            }
        }
        e->n_caracteres--;
        return c;
    }

// FUNÇÕES DE OPERAÇÃO DO EDITOR
    void inserir(Editor* e, char c, int posicao, int registra_undo) {
        inserir_texto(e, c, posicao);

        if(registra_undo) {
            desaloca_operacao(e->redo_list);
            e->redo_list = NULL;

            Operacao* new_op = malloc(sizeof(Operacao));
            new_op->tipo = 'I';
            new_op->caractere = c;
            new_op->posicao = posicao;
            new_op->prox = e->undo_list;
            e->undo_list = new_op;
        }
    }

    void remover(Editor* e, int posicao, int registra_undo) {
        if(posicao < 0 || posicao >= e->n_caracteres) return;

        char c = remover_texto(e, posicao);

        if(registra_undo) {
            desaloca_operacao(e->redo_list);
            e->redo_list = NULL;

            Operacao* novo = malloc(sizeof(Operacao));
            novo->tipo = 'R';
            novo->caractere = c;
            novo->posicao = posicao;
            novo->prox = e->undo_list;
            e->undo_list = novo;
        }
    }

// DESFAZER (UNDO)
    void undo_operacao(Editor* e) {
        if(e->undo_list == NULL) return;

        Operacao* un = e->undo_list;
        e->undo_list = un->prox;

        if(un->tipo == 'I') {
            remover_texto(e, un->posicao);
        } else {
            inserir_texto(e, un->caractere, un->posicao);
        }

        un->prox = e->redo_list;
        e->redo_list = un;
    }

// REFAZER (REDO)
    void redo_operacao(Editor* e) {
        if(e->redo_list == NULL) return;

        Operacao* re = e->redo_list;
        e->redo_list = re->prox;

        if(re->tipo == 'I') {
            inserir_texto(e, re->caractere, re->posicao);
        } else {
            remover_texto(e, re->posicao);
        }

        re->prox = e->undo_list;
        e->undo_list = re;
    }

// IMPRIMIR TEXTO
    void imprimir(Editor* e) {
        Texto *aux = e->tex;
        while(aux != NULL) {
            printf("%c", aux->caractere);
            aux = aux->prox;
        }
        printf("\n");
    }

// MAIN
int main() {
    Editor *edit = inicializa_editor();
    int n;
    if(scanf("%d", &n) != 1) {
        desaloca_editor(edit);
        return 0;
    }
    getchar(); 

    for(int i = 0; i < n; i++) {
        char c = getchar();
        if(c != '\n' && c != '\r') {
            inserir(edit, c, i, 0);
        } else {
            i--; 
        }
    }
    getchar();

    int m;
    if(scanf("%d", &m) != 1) {
        desaloca_editor(edit);
        return 0;
    }
    getchar();

    for(int i = 0; i < m; i++) {
        char op_tipo = getchar();
        if(op_tipo == '\n' || op_tipo == '\r') {
            op_tipo = getchar();
        }

        if(op_tipo == 'U') {
            undo_operacao(edit);
            char c = getchar();
            while(c != '\n' && c != EOF) {
                c = getchar();
            }
        } else if(op_tipo == 'E') {
            redo_operacao(edit);
            char c = getchar();
            while(c != '\n' && c != EOF) {
                c = getchar();
            }
        } else if(op_tipo == 'R') {
            int pos;
            scanf("%d", &pos);
            remover(edit, pos, 1);
            char c = getchar();
            while(c != '\n' && c != EOF) {
                c = getchar();
            }
        } else if(op_tipo == 'I') {
            char c_ins;
            int pos;
            scanf(" %c %d", &c_ins, &pos);
            inserir(edit, c_ins, pos, 1);
            char c = getchar();
            while(c != '\n' && c != EOF) {
                c = getchar();
            }
        }
        imprimir(edit);
    }

    desaloca_editor(edit);
    return 0;
}