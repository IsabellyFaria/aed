#include <stdio.h>
#include <stdlib.h>

void alcocar_vetor(float *v, int n){
    v = (float*) calloc(n, sizeof(float));
}
float calcular(float *c){}


int main(){
    int qtd = -1;
    while(qtd<0){
        printf("Digite quantas notas serão cadastradas: ");
        scanf("%d", &qtd);
    }

    float *v;
    alcocar_vetor(v, qtd);
    for (int i = 0; i < qtd; i++) {
        do {
            printf("Informe a %dª nota: ", i + 1);
            scanf("%f", &v[i]);
        } while (v[i] < 0);
    }

    float soma = 0;
    for(int i = 0; i < qtd; i++){
        soma += v[i];
    }
    float media = soma / qtd;
    
    printf("Média: %.2f", media);

    free(v);

    return 0;
}