#include <stdio.h>

//função para encontrar a saída
int encontrar_saida(int linhas, int colunas, char mapa[100][100], int inicio_l, int inicio_c) {
    //vetores para guardar as linhas, colunas e distâncias
    int fila_l[100 * 100]; //fila para guardar as linhas
    int fila_c[100 * 100]; //fila para guardar as colunas
    int fila_d[100 * 100]; //fila para guardar a distância percorrida
    
    //marcar por onde já passou
    int visitado[100][100] = {0};

    int inicio_fila = 0, fim_fila = 0;

    //pega as coordenadas iniciais e coloca na fila
    fila_l[fim_fila] = inicio_l;
    fila_c[fim_fila] = inicio_c;
    fila_d[fim_fila] = 0;
    fim_fila++; //aumenta indicando que tem um elemento na fila
    
    visitado[inicio_l][inicio_c] = 1; //marca a origem como visitada

    //vetores para as direções
    int direcao_l[] = {-1, 1, 0, 0};
    int direcao_c[] = {0, 0, -1, 1};
    //pegando cada coodenada de l x c e somando com a coodenada atual, obtem os vizinhos

    //loop da busca
    while (inicio_fila < fim_fila) { //enquanto tiver elementos na fila
        //tira o primeiro elemento das 3 filas
        int atual_l = fila_l[inicio_fila];
        int atual_c = fila_c[inicio_fila];
        int atual_d = fila_d[inicio_fila];
        inicio_fila++;

        //verifica se é a saída
        if (mapa[atual_l][atual_c] == 'd') {
            return atual_d; //a função termina aqui e devolve a distância
        }

        //testa os 4 vizinhos
        for (int i = 0; i < 4; i++) {
            int nova_l = atual_l + direcao_l[i];
            int nova_c = atual_c + direcao_c[i];

            //verifica se está dentro do mapa
            if (nova_l >= 0 && nova_l < linhas && nova_c >= 0 && nova_c < colunas) {
                //verifica se não é parede e não foi visitado
                if (mapa[nova_l][nova_c] != '#' && visitado[nova_l][nova_c] == 0) {
                    
                    visitado[nova_l][nova_c] = 1;
                    
                    //coloca o novo vizinho no final das 3 filas
                    fila_l[fim_fila] = nova_l;
                    fila_c[fim_fila] = nova_c;
                    fila_d[fim_fila] = atual_d + 1; //aumenta a distância em 1
                    fim_fila++;
                }
            }
        }
    }

    // -1 se n encontrou a saída
    return -1; 
}

int main() {
    int linhas, colunas;
    char mapa[100][100]; //matriz do mapa
    int inicio_l = -1, inicio_c = -1; //posição inicial

    //le as dimensões
    scanf("%dx%d", &linhas, &colunas);

    //le o mapa e procurando o 'o' da Rebeka
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf(" %c", &mapa[i][j]);
            if (mapa[i][j] == 'o') {
                inicio_l = i;
                inicio_c = j;
            }
        }
    }

    //chama a função para encontrar a saída
    int resultado = encontrar_saida(linhas, colunas, mapa, inicio_l, inicio_c);

    //prints finais
    if (resultado != -1) {
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", resultado);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}