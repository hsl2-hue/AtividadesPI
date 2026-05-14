#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** alocarMatriz(int linha, int coluna){
    int **matriz = (int **)malloc(linha * sizeof(int *));
    matriz[0] = (int *)malloc(linha * coluna * sizeof(int));
    for(int i = 1; i < linha; i++){
        matriz[i] = matriz[0] + i * coluna;
    }
    return matriz;
}

void liberarMemoriaMatriz(int** matriz){
    free(matriz[0]);
    free(matriz);
}

void copiarMatriz(int **original, int **copia, int linha, int coluna){
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            copia[i][j] = original[i][j];
        }
    }
}

void imprimirMatriz(int **matriz, int linha, int coluna){
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

// verifica se está no limite da matriz
int valido(int x, int y, int L, int C){
    if(x >= 0 && x < L && y >= 0 && y < C){
        return 1;
    } else {
        return 0;
    }
}

int obterCamada(int x, int y, int cx, int cy){
    int dx = abs(x - cx);
    int dy = abs(y - cy);

    if(dx + dy <= 1){
        return 1; //camada 1
    } else if (dx <= 2 && dy <= 2 && (dx + dy <= 3)){
        return 2; //camada 2
    } else {
        return 0;
    }
}
//habilidades de ataque
void explosao_arcana(int **matriz, int L, int C, int x, int y){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            int camada = obterCamada(i, j, x, y);
            int dano;

            if(camada == 1){
                dano = 50;
            } else if(camada == 2) {
                dano = 25;
            } else {
                dano = 0;
            }
            matriz[i][j] -= dano;
            if(matriz[i][j] < 0){
                matriz[i][j] = 0;
            }
        }
    }
    printf("Estado do mapa após usar a Explosão Arcana:\n");
    imprimirMatriz(matriz, L, C);
}

void nuvem_venenosa(int **matriz, int L, int C, int x, int y){
    printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");
    for(int turno = 1; turno <= 3; turno++){
        int vivos_na_area = 0;
        int** temp = alocarMatriz(L, C);
        copiarMatriz(matriz, temp, L, C);
        for(int i = 0; i < L; i++){
            for(int j = 0; j < C; j++){
                if(obterCamada(i, j, x, y) > 0){
                    int vizinhos_vivos = 0;
                    for(int dx = -1; dx <= 1; dx++){
                        for(int dy = -1; dy <= 1; dy++){
                            if(dx == 0 && dy == 0){
                                continue; //ignora o centro
                            }
                            if(valido(i + dx, j + dy, L, C)){
                                if(matriz[i + dx][j + dy] > 0){
                                    vizinhos_vivos++;
                                }
                            }
                        }
                    }
                    int dano = 5 + (8 * vizinhos_vivos);
                    temp[i][j] -= dano;
                    if(temp[i][j] < 0){
                        temp[i][j] = 0;
                    }
                }
                if(obterCamada(i, j, x, y) > 0){
                    if(temp[i][j] > 0){
                        vivos_na_area++;
                    }
                }
            }
        }
        copiarMatriz(temp, matriz, L, C);
        imprimirMatriz(matriz, L, C);
        printf("\n");
        liberarMemoriaMatriz(temp);
        if(vivos_na_area == 0){
            break; //todos os inimigos na área foram eliminados
        }
    }
}

int main(){
    int L, C, x, y;
    int **matriz;
    char ataque[20];

    scanf("%d %d", &L, &C);

    matriz = alocarMatriz(L, C);

    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    scanf("%d %d", &x, &y);
    scanf("%s", ataque);

    printf("Estado inicial do mapa:\n");
    imprimirMatriz(matriz, L, C);
    printf("\n");

    void (*ataqueFuncao)(int**, int, int, int, int) = NULL; // Ponteiro para função de ataque
    if(strcmp(ataque, "EXPLOSAO_ARCANA") == 0){
        ataqueFuncao = explosao_arcana;
    } else if(strcmp(ataque, "NUVEM_VENENOSA") == 0){
        ataqueFuncao = nuvem_venenosa;
    }
    int **copiaMatriz = alocarMatriz(L, C);
    copiarMatriz(matriz, copiaMatriz, L, C);
    if(ataqueFuncao != NULL){
        ataqueFuncao(copiaMatriz, L, C, x, y);
    }

    liberarMemoriaMatriz(copiaMatriz);

    liberarMemoriaMatriz(matriz);
    return 0;
}