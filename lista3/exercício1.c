#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(){
    int T, N; //n?mero de casos de teste
    scanf("%d", &T);

    while(T--){
        scanf("%d", &N);// tamanho da sequ?ncia

        int arr[100]; //vetor para armazenar a sequ?ncia
        for(int i = 0; i < N; i++){
            scanf("%d", &arr[i]);
        }

        if(N < 2){ //se o vetor for muito pequeno, n?o h? sequ?ncia decrescente
            printf("0\n");
            continue;
        }

        int tamMax = 0;
        int comecoOriginal = 0;
        int tamAtual = 1;
        int comecoAtual = 0;

        for (int i = 1; i < N; i++){
            if(arr[i] < arr[i-1]){ //verifica se o n?mero atual ? menor que o anterior (decrescente)
                tamAtual++;
            } else { //se parou de descer, verific se foi a maior at? agora
                if(tamAtual > tamMax){
                    tamMax = tamAtual;
                    comecoOriginal = comecoAtual;
                }
                //reseta os contadores para iniciar uma nova busca
                tamAtual = 1;
                comecoAtual = i;
            }
        }
        //caso termine no ultimo elemento, verifica uma ?ltima vez
        if (tamAtual > tamMax){
            tamMax = tamAtual;
            comecoOriginal = comecoAtual;
        }

        if (tamMax < 2){ //se a maior sequ?ncia tiver tamanho 1, significa que nada decresceu
            printf("0\n");
        } else {
            printf("%d\n", tamMax); //imprime o tamanho
            
            for(int i = 0; i < tamMax; i++){
                printf("%d", arr[comecoOriginal + i]); //imprime os valores da sequ?ncia
                if(i < tamMax){
                    printf(" "); //imprime um espa?o entre os n?meros, mas n?o depois do ?ltimo
                }
            }
            printf("\n"); //nova linha ap?s imprimir a sequ?ncia
        }
        
    }

    return 0;
}
