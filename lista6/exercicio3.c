#include <stdio.h>
#include <stdlib.h>

/* comando 1 = valor + 5
comando 2 = if valor > 80 : valor = 80
comando 3 = valor * 2
comando 4 = 
comando 0 = encerra
*/ 

int** alocacao(int linha, int coluna){
    int **matriz = (int **)malloc(linha * sizeof(int *));
    matriz[0] = (int *)malloc(linha * coluna * sizeof(int));
    for(int i = 1; i < linha; i++){
        matriz[i] = matriz[0] + i * coluna;
    }
    return matriz;
}

void liberarMemoria(int** matriz){
    free(matriz[0]);
    free(matriz);
}

void imprimirMatriz(int** matriz, int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            if(j == coluna - 1){
                printf("%d", matriz[i][j]);
            } else {
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

int calibracao(int valor){
    return valor + 5;
}

int saturacao(int valor){
    if(valor > 80){
        return 80;
    } else {
        return valor;
    }
}

int amplificador(int valor){
    return valor * 2;
}

void modificar(int **matriz, int linha, int coluna, int(*pipeline[])(int), int k){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            for(int f = 0; f < k; f++){
                matriz[i][j] = pipeline[f](matriz[i][j]); //chama a função apontada por f
            }
        }
    }
}

int main(){
    int N, M;
    int **matriz;

    scanf("%d %d", &N, &M);

    matriz = alocacao(N, M);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    int (*funcoes_base[4])(int) = {NULL, calibracao, saturacao, amplificador}; //fica certo pra ser 1, 2, 3

    int comando;
    while(scanf("%d", &comando) && comando != 0){
        int k; //quantidade de filtros na pipeline
        int(**pipeline_atual)(int) = NULL;

        if(comando >= 1 && comando <= 3){
            k = 1;
            pipeline_atual = malloc(k * sizeof(int (*)(int)));
            pipeline_atual[0] = funcoes_base[comando];
        } else if(comando == 4){
            scanf("%d", &k);
            pipeline_atual = malloc(k * sizeof(int (*)(int)));
            for(int i = 0; i < k; i++){
                int id; //qual comando
                scanf("%d", &id);
                pipeline_atual[i] = funcoes_base[id];
            }
        }
        if(pipeline_atual){
            modificar(matriz, N, M, pipeline_atual, k);
            free(pipeline_atual);
        }
    }

    //encontrar o maior valor
    printf("Matriz processada:\n");
    imprimirMatriz(matriz, N, M);

    int maior = matriz[0][0], linha_c = 0, coluna_c = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j ++){
            if(matriz[i][j] > maior){
                maior = matriz[i][j];
                linha_c = i;
                coluna_c = j;
            }
        }
    }
    printf("\nSensor critico: %d\n", maior);
    printf("Posicao: (%d,%d)\n", linha_c, coluna_c);

    liberarMemoria(matriz);

    return 0;
}
