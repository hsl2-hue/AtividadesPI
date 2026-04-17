#include <stdio.h>

int m, n;
char parede[100][100]; //matriz q representa a parede
int gotaInicial_L[100 * 100];
int gotaInicial_C[100 * 100];

//função recursiva para simular o trajeto da água
//recebe a linha e a coluna atual da agua
void fluxo(int l, int c) {
    //se a água sair dos limites da matriz, encerra a rota
    if (l < 0 || l >= m || c < 0 || c >= n) return;
    
    //se encontrar uma prateleira ou uma gota de água já processada, encerra
    if (parede[l][c] == '#' || parede[l][c] == 'o') return;

    //marca a posição atual com água
    parede[l][c] = 'o';

    //verifica o elmento imediatamente abaixo
    if (l + 1 < m) {
        if (parede[l+1][c] == '.') {
            //se estiver vazio abaixo, a água continua caindo reto
            fluxo(l+1, c);
        } else if (parede[l+1][c] == '#') {
            //se bater em uma prateleira abaixo, a água se espalha para os lados
            fluxo(l, c-1);
            fluxo(l, c+1);
        }
    }
}

int main() {
    //le as dimensões da parede
    scanf("%d %d", &m, &n);

    //lê as linhas da matriz
    for (int i = 0; i < m; i++) {
        scanf("%s", parede[i]);
    }

    int gotasIniciais = 0; //contador

    //procura todas as gotas iniciais na parede
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (parede[i][j] == 'o') {
                // Guarda a coordenada da gota
                gotaInicial_L[gotasIniciais] = i; //salva a linha
                gotaInicial_C[gotasIniciais] = j; //salva a coluna
                gotasIniciais++;
                // Limpa o local para a função de simulação preencher corretamente
                parede[i][j] = '.'; //apaga a gota original para a funçaõ fluxo preencher sem conflito
            }
        }
    }

    //inicia a simulação para cada gota inicial encontrada
    for (int i = 0; i < gotasIniciais; i++) {
        fluxo(gotaInicial_L[i], gotaInicial_C[i]);
    }

    //imprime o resultado final
    for (int i = 0; i < m; i++) {
        printf("%s\n", parede[i]);
    }

    return 0;
}