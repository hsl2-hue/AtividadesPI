#include <stdio.h>
#include <stdlib.h>

int main() {
    int *lugares = NULL; //ponteiro para armazenar os números lidos
    int numero;
    int contador = 0;

    //le ate o fim da entrada
    while (scanf("%d", &numero) != EOF) {
        // Aumenta o espaço alocado para acomodar mais um inteiro
        int *temp = realloc(lugares, (contador + 1) * sizeof(int));
        lugares = temp;
        lugares[contador] = numero;
        contador++;
    }

    //print inicial
    printf("Mais um bom dia de trabalho!\n");

    //print de numeros ímpares
    for (int i = 0; i < contador; i++) {
        if (lugares[i] % 2 != 0) {
            printf("%d\n", lugares[i]);
        }
    }

    //print de numeros pares
    for (int i = 0; i < contador; i++) {
        if (lugares[i] % 2 == 0) {
            printf("%d\n", lugares[i]);
        }
    }

    //print final
    printf("Vou visitar esses lugares de novo... algum dia.\n");

    //liberar a memória alocada
    free(lugares);

    return 0;
}