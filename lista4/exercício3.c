#include <stdio.h>

//faz o trajeto de pedro
void rastrearCaminho(char linha[], int cidade[150][150], int destino[2]) {
    int x = 0;
    int y = 0;
    int passos_lidos = 0;

    //marca o ponto de partida na matriz
    cidade[y][x] += 1;

    for (int i = 0; linha[i] != '\0' && passos_lidos < 20; i++) {
        char movimento = linha[i];

        if (movimento == ' ' || movimento == '\n') {
            continue; 
        }

        passos_lidos++;

        switch (movimento) {
            case 'c': y--; break; // Cima
            case 'b': y++; break; // Baixo
            case 'e': x--; break; // Esquerda
            case 'd': x++; break; // Direita
        }

        //se tiver dentro da matriz
        if (x >= 0 && x < 150 && y >= 0 && y < 150) {
            cidade[y][x] += 1;
        }
    }

    //salva o destino final de pedro
    destino[0] = x; // 0 = X
    destino[1] = y; // 1 = Y
}

//analisa a matriz e acha o local mais visitado
void encontrarMaisVisitado(int cidade[150][150], int perigo[2]) {
    int max_visitas = -1; 

    for (int linha = 0; linha < 150; linha++) {
        for (int coluna = 0; coluna < 150; coluna++) {
            
            if (cidade[linha][coluna] > max_visitas) {
                max_visitas = cidade[linha][coluna]; 
                
                //salva as coordenadas de manuela
                perigo[0] = coluna; // X
                perigo[1] = linha;  // Y
            }
        }
    }
}

int main() {
    char linha[100]; 
    int matriz_cidade[150][150] = {0}; 
    
    //inicializa com {0, 0}
    int coordenada_destino[2] = {0, 0}; 
    int coordenada_manuela[2] = {0, 0}; 

    //lê a entrada do usuário
    fgets(linha, sizeof(linha), stdin);

    //chama as funçoes
    rastrearCaminho(linha, matriz_cidade, coordenada_destino);
    encontrarMaisVisitado(matriz_cidade, coordenada_manuela);

    //print
    printf("Coordenada X: %d, Y: %d\n", coordenada_manuela[0], coordenada_manuela[1]);

    return 0;
}