#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float media(float *notas, int alunos){
    float soma = 0;
    for(int i = 0; i < alunos; i++){
        soma += notas[i];
    }
    return soma / alunos;
}

float maior_nota(float *notas, int alunos, int *posicao){
    float maior = notas[0];
    *posicao = 1; //posição do primeiro aluno
    for(int i = 1; i < alunos; i++){
        if(notas[i] > maior){
            maior = notas[i];
            *posicao = i + 1;
        }
    }
    return maior;
}

float menor_nota(float *notas, int alunos, int *posicao){
    float menor = notas[0];
    *posicao = 1; //posição do primeiro aluno
    for(int i = 1; i < alunos; i++){
        if(notas[i] < menor){
            menor = notas[i];
            *posicao = i + 1;
        }
    }
    return menor;
}

int acima_da_media(float * notas, int alunos, float media){
    int contador = 0;
    for(int i = 0; i < alunos; i++){
        if(notas[i] > media){
            contador++;
        }
    }
    return contador;
}

float mediana(float *notas, int alunos){
    float *copia = (float*) malloc(alunos * sizeof(float));
    for(int i = 0; i < alunos; i++){
        copia[i] = notas[i];
    }
    //bubble sort para ordenar as notas
    for(int i = 0; i < alunos - 1; i++){
        for(int j = 0; j < alunos - i - 1; j++){
            if (copia[j] > copia[j + 1]){
                float temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }
    float mediana;
    if(alunos % 2 == 0){
        mediana = (copia[(alunos / 2) - 1] + copia[alunos / 2]) / 2.0;
    } else {
        mediana = copia[alunos / 2];
    }
    free(copia);
    return mediana;
}

float moda(float *notas, int alunos, int *moda_unica){
    float moda = -1;
    int max_frequencia = 0;
    *moda_unica = 1; //assume que a moda é única inicialmente

    for(int i = 0; i < alunos; i++){ 
        int frequencia_atual = 0;
        //quantas vezes a nota atual aparece
        for(int j = 0; j < alunos; j++){
            if(notas[i] == notas[j]){
                frequencia_atual++;
            }
        }
        if(frequencia_atual > max_frequencia){
            max_frequencia = frequencia_atual;
            moda = notas[i];
            *moda_unica = 1; //nova moda encontrada, assume que é única
        } else if(frequencia_atual == max_frequencia && notas[i] != moda){
            *moda_unica = 0; //encontrada outra nota com a mesma frequência, moda não é única
        }
    }
    return moda;
}

void relatorio(float *notas, int alunos){
    float media_notas = media(notas, alunos);

    int posicao_maior, posicao_menor;
    float maior = maior_nota(notas, alunos, &posicao_maior);
    float menor = menor_nota(notas, alunos, &posicao_menor);

    int acima_media = acima_da_media(notas, alunos, media_notas);

    float mediana_notas = mediana(notas, alunos);

    int moda_unica;
    float moda_notas = moda(notas, alunos, &moda_unica);

    //imprimir relatorio
    printf("Media: %.2f\n", media_notas);
    printf("Maior nota: %.2f (aluno %d)\n", maior, posicao_maior);
    printf("Menor nota: %.2f (aluno %d)\n", menor, posicao_menor);
    printf("Acima da media: %d\n", acima_media);
    printf("Mediana: %.2f\n", mediana_notas);
    if(moda_unica){
        printf("Moda: %.2f\n", moda_notas);
    } else {
        printf("Moda: Nao ha moda unica\n");
    }
}

int main(){
    int n, k;
    scanf("%d", &n);

    float *notas = (float*) malloc(n * sizeof(float));
    for(int i = 0; i < n; i++){
        scanf("%f", &notas[i]);
    }

    printf("Relatorio inicial\n");
    relatorio(notas, n);
    scanf("%d", &k);

    if(k > 0){
        float *temp = (float*) realloc(notas, (n + k) * sizeof(float));
        notas = temp;
        for(int i = n; i < n + k; i++){
            scanf("%f", &notas[i]);
        }
    }

    printf("\nRelatorio atualizado\n");
    relatorio(notas, n + k);

    free(notas);

    return 0;
}