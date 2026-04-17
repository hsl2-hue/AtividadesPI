#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char s[101]; //onde guarda as entradas
    char *palavras[50]; //cria um vetor ponteiro, para guardar apenas onde a palavra come�a
    int totalPalavras = 0;
    int totalAnagramas = 0;
    int i, j, k;

    // leitura da entrada
    fgets(s, 101, stdin);
    s[strcspn(s, "\n")] = '\0'; //procura \n e substitui por \0 pra n contar o enter

    // separa��o das palavras
    int emPalavra = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) { //verifica se � letra
            if (!emPalavra) {
                palavras[totalPalavras++] = &s[i]; //guarda o endere�o das strings
                emPalavra = 1;
            }
        } else {
            s[i] = '\0'; //coloca \0 onde n for letra pra dividir em strings menores
            emPalavra = 0;
        }
    }

    //verifica se tem anagramas antes do print
    int primeiroPar = 1; //flag para imprimir o cabe�alho apenas uma vez

    for (i = 0; i < totalPalavras; i++) {
        for (j = i + 1; j < totalPalavras; j++) { //j=i+1 para a palavra n se comparar com ela
            
            int saoAnagramas = 1; //come�a verdadeiro 
            int contagem[26] = {0}; //zera a contagem

            if (strlen(palavras[i]) != strlen(palavras[j])) {
                saoAnagramas = 0;
            } else {
                for (k = 0; palavras[i][k] != '\0'; k++) {
                    //pega a letra e diminui de 'a' para pegar o indice
                    contagem[tolower(palavras[i][k]) - 'a']++;
                    contagem[tolower(palavras[j][k]) - 'a']--;
                    //vai somar e subtair, pq se sobrar 0 no final quer diver q as letras eram iguais
                }
                for (k = 0; k < 26; k++) {
                    if (contagem[k] != 0) {
                        saoAnagramas = 0;
                        break;
                    }
                }
            }

            if (saoAnagramas) {
                // se o primeiro par for encontrado
                if (primeiroPar) {
                    printf("Pares de anagramas encontrados:\n");
                    primeiroPar = 0;
                }
                printf("%s e %s\n", palavras[i], palavras[j]); //printa os pares
                totalAnagramas++;
            }
        }
    }

    //exibe o total
    if (totalAnagramas > 0) {
        printf("\nTotal de pares: %d\n", totalAnagramas);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }

    return 0;
}