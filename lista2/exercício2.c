#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(){
    int N, K, P;
    scanf("%d %d %d", &N, &K, &P);

    int primeiroEncontrado = -1;
    int Q = 0;
    for(int i = N; i < K; i++){
        int copia = i; //cria uma c�pia para fazer qa fatora��o
        int fatoresImpares = 0; //contador de impares
        int valido = 1; // booleana verdadeira at� ser negada

        while(copia > 0 && copia % 2 == 0){
            copia = copia / 2; // vai removendo os fatores pares
        }

        // fatora��o por primos
        for (int d = 3; d * d <= copia; d += 2){
            if(copia % d == 0){
                fatoresImpares++;
                copia = copia / d;
                if (copia % d == 0){
                    valido = 0; // n pode ser divis�vel por d de novo
                    break;
                } 
            }
        }

        if (valido == 1 && copia > 1) {
            fatoresImpares ++; 
        }

        if (valido == 1 && fatoresImpares == P){
            if (primeiroEncontrado == -1){
                primeiroEncontrado = i;
            } else {
                Q++;
            }
        }
    }

    // prints
    if (primeiroEncontrado != -1){
        printf("%d %d\n", primeiroEncontrado, Q);
    } else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }

    return 0;
}