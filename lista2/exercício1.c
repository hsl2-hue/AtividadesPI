#include <stdio.h>

int main(){
    char letra;
    scanf("%c", &letra);
    
    // A == 65 e Z == 90
    int n = letra - 'A' + 1; // com isso converte pra n�mero, e come�a de 1
    
    //percorre cada linha q tiver
    for(int i = 1; i <= n; i++) {
        //coloca primeiro os pontos a partir de B
        for(int j = 1; j <= n - i; j++){
            printf(".");
        }
        //imprime em ordem crescente
        for(int j = 0; j < i; j++){
            printf("%c", 'A' + j);
        }
        //imprime em ordem decrescente
        for(int j = i - 2; j >= 0; j--){
            printf("%c", 'A' + j);
        }
        //depois os pontos de novo
        for(int j = 1; j <= n - i; j++){
            printf(".");
        }
        //pula quando terminar a linha
        printf("\n");
    }
    // tinha esquecido q a ordem dos for impota
    return 0;
}
