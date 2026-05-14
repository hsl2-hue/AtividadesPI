#include <stdio.h>
#include <stdlib.h>

int** alocarMatriz(int linha, int coluna){
    int **matriz = (int **)malloc(linha * sizeof(int *));    
    matriz[0] = (int *)malloc(linha * coluna * sizeof(int));

    for(int i = 1; i < linha; i++){
        matriz[i] = matriz[0] + i * coluna;
    }
    return matriz;
}

void lerMatriz(int **matriz, int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
}

void imprimirMatriz(int **matriz, int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarMemoriaMatriz(int** matriz){
    free(matriz[0]);
    free(matriz);
}

int dobro(int valor){
    return valor * 2;
}

int quadrado(int valor){
    return valor * valor;
}

int absoluto(int valor){
    if(valor < 0){
        return -valor;
    }
    return valor;
}

void aplicarOperacao(int **matriz, int linha, int coluna, int (*operacao)(int)){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            matriz[i][j] = operacao(matriz[i][j]);
        }
    }
}

int main(){
    int L, C, O;
    int **matriz;
    scanf("%d %d", &L, &C);
    
    matriz = alocarMatriz(L, C);
    lerMatriz(matriz, L, C);
    
    scanf("%d", &O);

    switch (O) {
        case 1:
            aplicarOperacao(matriz, L, C, dobro);
            break;
        case 2:
            aplicarOperacao(matriz, L, C, quadrado);
            break;
        case 3:
            aplicarOperacao(matriz, L, C, absoluto);
            break;
        default:
            break;
    }

    imprimirMatriz(matriz, L, C);

    liberarMemoriaMatriz(matriz);
    return 0;
}