#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int N, X, Y;
    
    //incializa��o e coleta dos dados
    scanf("%d %d %d", &N, &X, &Y);

    //array para armazenar as latas de cada um dos N clientes
    //inicializo todos com 0
    int latas[N + 1]; // +1 para come�ar do 1 ao inves do 0
    for (int i = 0; i <= N; i++) {
        latas[i] = 0;
    }

    //clientes m�ltiplos de X compraram 1 lata
    if (X > 0) {
        for (int i = X; i <= N; i += X) {
            latas[i] = 1;
        }
    }

    // registra quem comprou mais de 1 lata
    for (int j = 0; j < Y; j++) {
        int h, m, Z;
        //le no formato HH:MM Z
        scanf("%d:%d %d", &h, &m, &Z);

        //converte hor�rio para posi��o na fila
        int minutos_totais = (h * 60) + m;
        int posicao = (minutos_totais - 420) / 3;

        // o registro do sistema sobrep�e a regra do m�ltiplo
        if (posicao >= 1 && posicao <= N) {
            latas[posicao] = Z;
        }
    }

    // soma latas e encontrar o vencedor
    int soma = 0;
    int ganhador = -1;

    for (int i = 1; i <= N; i++) {
        soma += latas[i];

        if (soma >= 50) {
            ganhador = i;
            break;
        }
    }

    // prints
    if (ganhador != -1) {
        // calcula o hor�rio do ganhador para a sa�da
        int minutos_ganhador = 420 + (ganhador * 3);
        int hora_final = minutos_ganhador / 60;
        int min_final = minutos_ganhador % 60;
        if (latas[ganhador] == 1){
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.\n", ganhador, hora_final, min_final, latas[ganhador]);
        } else {
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n", ganhador, hora_final, min_final, latas[ganhador]);
        }
    } else {
        int faltam = 50 - soma;
        if (faltam == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta %d lata.\n", faltam);
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", faltam);
        }
    }

    return 0;
}