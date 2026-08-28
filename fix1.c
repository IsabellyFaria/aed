#include <stdio.h>
#include <stdlib.h>

float* alcocar_vetor(int n) {
    return (float*) calloc(n, sizeof(float));
}
float calcular_media(float *v, int qtd){
    float soma = 0;
        for(int i = 0; i < qtd; i++){
            soma += *(v+i);
        }
        float media = soma / qtd;

    return media;
}


int main(){
    int qtd = -1;
    while(qtd<=0){
        printf("Digite quantas notas serão cadastradas: ");
        scanf("%d", &qtd);
    }

    float *v = alcocar_vetor(qtd);
    for (int i = 0; i < qtd; i++) {
        do {
            printf("Informe a %dª nota: ", i + 1);
            scanf("%f", &v[i]);
        } while (v[i] < 0);
    }
    float m = calcular_media(v, qtd);
    
    printf("Média: %.2f", m);

    free(v);

    return 0;
}