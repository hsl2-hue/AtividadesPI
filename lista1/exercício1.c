#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    // declaro e coleto as variaveis do input
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;
    scanf("%d/%d/%d %d/%d/%d", &dia1, &mes1, &ano1, &dia2, &mes2, &ano2);

    // faço os cálculos das previsões com base nas intruções no enunciado
    int amor = ((dia1 + mes1 + ano1 + dia2 + mes2 + ano2) * 7) % 101;
    int sorte = (((dia1 + dia2 + mes1 + mes2) * 9 + ano2 - ano1) % 101);
    int trabalho = (((ano1 + ano2) - (dia1 + dia2 + mes1 + mes2) * 8) % 101);
    int cor = ((dia1 * dia1 + dia2 * dia2) + (mes1 * mes1 + mes2 * mes2) + (ano1 * ano1 + ano2 * ano2)) % 11;

    // as condincionais para cada previsão 
    // Amor
    if (amor < 20) {
        printf("Amor: %d%% Pessimo dia para se apaixonar.\n", amor);
    } else if (amor >= 20 && amor <= 40) {
        printf("Amor: %d%% Melhor manter o coracao <3 longe de perigo.\n", amor);
    } else if (amor >= 41 && amor <= 69) {
        printf("Amor: %d%% Se o papo e as ideias baterem, esta liberado pensar em algo.\n", amor);
    } else if (amor >= 70 && amor <= 80) {
        printf("Amor: %d%% Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n", amor);
    } else {
        printf("Amor: %d%% Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n", amor);
    }

    //Sorte
    if (sorte < 30) {
        printf("Sorte: %d%% Nem jogue moedas pra cima hoje. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else if (sorte >= 30 && sorte <= 50) {
        printf("Sorte: %d%% Melhor nao arriscar. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else if (sorte >= 51 && sorte <= 79) {
        printf("Sorte: %d%% Por sua conta em risco. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else if (sorte >= 80 && sorte <= 90) {
        printf("Sorte: %d%% Hoje vale a pena arriscar. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    } else {
        printf("Sorte: %d%% Nao tenha medo de virar cartas hoje. Sem tigrinho nem jogos de azar, por favor!\n", sorte);
    }

    //Trabalho
    if (trabalho < 40) {
        printf("Trabalho: %d%% Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n", trabalho);
    } else if (trabalho >= 40 && trabalho <= 50) {
        printf("Trabalho: %d%% Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n", trabalho);
    } else if (trabalho >= 51 && trabalho <= 69) {
        printf("Trabalho: %d%% Um dia proveitoso com certeza, leve sua simpatia consigo.\n", trabalho);
    } else if (trabalho >= 70 && trabalho <= 84) {
        printf("Trabalho: %d%% Boas vibracoes hoje, chances podem estar ao seu redor.\n", trabalho);
    } else {
        printf("Trabalho: %d%% Use do maximo de networking possível hoje, dia bom para negocios.\n", trabalho);
    }

    //Cor
    if (cor == 0) {
        printf("Cor: Cinza.\n");
    } else if (cor == 1) {
        printf("Cor: Vermelho.\n");
    } else if (cor == 2) {
        printf("Cor: Laranja.\n");
    } else if (cor == 3) {
        printf("Cor: Amarelo.\n");
    } else if (cor == 4) {
        printf("Cor: Verde.\n");
    } else if (cor == 5) {
        printf("Cor: Azul.\n");
    } else if(cor == 6) {
        printf("Cor: Roxo.\n");
    } else if (cor == 7) {
        printf("Cor: Marrom.\n");
    } else if (cor == 8) {
        printf("Cor: Rosa.\n");
    } else if (cor == 9) {
        printf("Cor: Preto.\n");
    } else if (cor == 10) {
        printf("Cor: Branco.\n");
    }
    
    return 0;
}
