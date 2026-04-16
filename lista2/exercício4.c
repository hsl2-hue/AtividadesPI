#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main() {
    int q;
    // L� a quantidade de instru��es
    scanf("%d", &q);

    int coluna = 0;
    int primeira = 1;       // Indica se � a primeira instru��o
    int ultimoFoiB = 0;   // 

    for (int i = 0; i < q; i++){
        int X;
        char movimento;
        scanf("%d %c", &X, &movimento); // le a quantidade e o movimento q vai fazer

        // para a primeira instru��o
        if(primeira){
            if(movimento == 'D'){
                for(int j = 0; j < X; j++) putchar('.'); // imprime os pontos
                putchar('\n');
                coluna = X - 1; // o cursor para no ultimo ponto
            } else if(movimento == 'E'){
                // a primeira n pode ir pra esquerda se come�a no 0
                printf("Informacao invalida\n");
                return 0;
            } else if(movimento == 'B'){
                for(int j = 0; j < X; j++){
                    for(int k = 0; k < coluna; k++) putchar(' '); // imprime os espa�os
                    printf(".\n");
                }
                ultimoFoiB = 1;
            }
            primeira = 0; // marca q n � mais a primeira
        } else { // para as prox instru��es
            if(movimento == 'D'){
                for (int j = 0; j < coluna; j++) putchar(' '); // imprime os espa�os vazios at� a coluna atual

                for (int j = 0; j < X + 1; j++) putchar('.'); // X + o ponto de origem
                putchar('\n');

                coluna = coluna + X; // atualiza a coluna
                ultimoFoiB = 0; // fechou a linha horizontal
            } else if (movimento == 'E'){
                int nova = coluna - X; // calcula a nova posi��o
                if(nova < 0){
                    // se a nova posi��o for negativa, � inv�lida
                    printf("Informacao invalida\n");
                    return 0;
                }

                for (int j = 0; j < nova; j++) putchar(' '); // imprime os espa�os at� a nova margem esquerda
                for (int j = 0; j < X + 1; j++) putchar('.'); // imprime os pontos
                putchar('\n');

                coluna = nova; // atualiza a coluna
                ultimoFoiB = 0;
            } else if (movimento == 'B'){
                // ao descer, imprime apenas as linhas interm�dias
                // a ultima linha fica esperando a prox instru��o
                for (int j = 0; j < X - 1; j++){
                    for (int k = 0; k < coluna; k++) putchar(' '); // imprime os espa�os
                    printf(".\n");
                }
                ultimoFoiB = 1;
            }
        }

    }
    // se a �ltima instru��o foi 'B', imprime a linha final
    if (ultimoFoiB){
        for(int m = 0; m < coluna; m++) putchar(' ');
        printf(".\n");
    }

    return 0;
}