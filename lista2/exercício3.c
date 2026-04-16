#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*Se dois termos da sequ�ncia dentro de um mesmo canal estiverem � mesma dist�ncia do n�mero fornecido, 
pegue o menor. 
Se dois termos das sequ�ncias de dois canais diferentes estiverem � mesma dist�ncia do n�mero,
pegue o canal de �ndice maior.*/

int main(){
    long long X; // numero fornecido pelo site
    int N; // quantos casnais existem, os numeros da sequencia de cada canal vai at� N
    scanf("%lld %d", &X, &N);

    long long melhorDistancia = -1; // melhor distancia encontrada
    int melhorCanal = -1; // canal com melhor resultado
    int melhorMinuto = -1; // minuto em q o melhor resultado foi encontrado
    long long melhorTermo = -1; // melhor termo encontrado

    //O �ndice de cada canal vai de 1 at� N.
    for (int canal = 1; canal <= N; canal++){
        long long f1, f2;
        scanf("%lld %lld", &f1, &f2); // le os 2 n�meros que representam os dois n�meros iniciais da sequ�ncia de cada canal. 

        long long antigo = f1, atual = f2; // guarda os dois �ltimos minutos
        int minuto = 1; // come�a a contar o tempo

        long long melhorDistancia1 = llabs(f1 - X); // distancia de f1 para X
        int melhorMinuto1 = 1; // minuto em que f1 foi no minuto 1
        long long melhorTermo1 = f1; // guarda f1

        // Verifica f2
        long long d = llabs(f2 - X); // distancia de f2 para X
        if (d < melhorDistancia1){ // pega a menor distancia
            melhorDistancia1 = d; // atualiza a melhor distancia
            melhorMinuto1 = 2; // atualiza o minuto
            melhorTermo1 = f2; // guarda f2
        }

        // Gera os pr�ximos termos at� ultrapassar X e o termo seguinte
        minuto = 2; // come�a a contar a partir do minuto 2
        while (atual < X){
            long long proximo = antigo + atual; // calcula o prox
            minuto++; // incrementa o minuto
            d = llabs(proximo - X); // distancia do pr�ximo termo para X
            if (d < melhorDistancia1){
                melhorDistancia1 = d; // atualiza a melhor distancia
                melhorMinuto1 = minuto;
                melhorTermo1 = proximo; // guarda o pr�ximo termo
            }
            antigo = atual;
            atual = proximo;
        }

        // Um termo extra ap�s ultrapassar X, para ter a certeza absoluta de que n�o h� um n�mero mais pr�ximo ali � frente.
        long long proximo = antigo + atual;
        minuto++;
        d = llabs(proximo - X);
        if (d < melhorDistancia1){
            melhorDistancia1 = d;
            melhorMinuto1 = minuto;
            melhorTermo1 = proximo;
        }

        // atualiza os globai s
        if (melhorDistancia == -1 || melhorDistancia1 < melhorDistancia || (melhorDistancia1 == melhorDistancia && canal > melhorCanal)){
           melhorDistancia = melhorDistancia1;
            melhorCanal = canal;
            melhorMinuto = melhorMinuto1;
            melhorTermo = melhorTermo1;
        }
    }

    int vip = 0;
    long long termo = melhorTermo;
    // soma os d�gitos do melhor termo encontrado
    while(termo > 0){
        vip = vip + termo % 10; // soma os d�gitos do melhor termo encontrado
        termo = termo / 10; // remove o �ltimo d�gito
    }
    vip = vip > 10; // verifica se a soma dos d�gitos � maior que 10

    // prints 
    if (vip){
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", melhorCanal, melhorMinuto);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP n�o vai rolar :(\n", melhorCanal, melhorMinuto);
    }


    return 0;
}