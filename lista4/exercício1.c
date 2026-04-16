#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//le a entrada e prepara as matrizes.
void lerMatriz(int m, int n, char praca[][100], char resultado[][100]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &praca[i][j]);
            resultado[i][j] = praca[i][j]; // Começa sendo igual ao original
        }
    }
}

//percorre a matriz para encontrar os postes e aplicar as regras de enfeite
void processarEnfeites(int m, int n, char praca[][100], char resultado[][100]) {
    //vê cada posição para encontrar postes 'P'
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (praca[i][j] == 'P') {
                
                //verifica os vizinhos ao redor do poste
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di; // nova linha
                        int nj = j + dj; // nova coluna

                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && praca[ni][nj] == '-') {
                            
                            //regra para as diagonais
                            if (di != 0 && dj != 0) {
                                //coloca 'x' apenas se a posição no resultado ainda estiver vazia
                                if (resultado[ni][nj] == '-') {
                                    resultado[ni][nj] = 'x';
                                }
                            } 
                            //regra para as 4 posições ortogonais
                            else if (di != 0 || dj != 0) {
                                // '+' sempre prevalece
                                resultado[ni][nj] = '+';
                            }
                        }
                    }
                }
            }
        }
    }
}

//mostra o resultado final
void imprimirMatriz(int m, int n, char resultado[][100]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", resultado[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n;
    
    //lê as dimensões da praça
    scanf("%d %d", &m, &n);

    char praca[100][100]; 
    char resultado[100][100];

    lerMatriz(m, n, praca, resultado);

    processarEnfeites(m, n, praca, resultado);

    imprimirMatriz(m, n, resultado);

    return 0;
}
