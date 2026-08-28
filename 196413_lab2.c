#include <stdio.h>
#include <stdlib.h>

int **alocar_matriz(int m, int n){
    int **v = calloc(m, sizeof(int*));
    for(int i = 0; i < m; i++){
        v[i] = calloc(n, sizeof(int*));
    }

    return v;
}

int **transpor_matriz(int **matriz, int m, int n){
    int **v = alocar_matriz(n,m);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            v[j][i] = matriz[i][j];
        }
    }
    return v;
}

void imprimir_matriz(int **matriz, int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberar_matriz(int **matriz, int linhas){
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int **matriz = alocar_matriz(m,n);
    for(int i = 0; i<m; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
    int **transposta = transpor_matriz(matriz, m, n);

    imprimir_matriz(transposta,n,m);
    
    liberar_matriz(matriz, m);
    liberar_matriz(transposta, n);
    return 0;
}