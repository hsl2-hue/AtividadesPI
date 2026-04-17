#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int R;
    
    //inicializa e coleta R
    scanf("%d", &R);

    //array muito grande pa luz final
    char luz_gigante[100000] = ""; 
    
    for (int i = 0; i < R; i++) {
        char S[100]; //string para guardar o fio atual
        int F;       //flashes
        
        //coleta a configura��o do fio e o n�mero de flashes
        scanf("%s %d", S, &F);
        
        int len = strlen(S);
        
        for (int f = 0; f < F; f++) {
            int indice = 0;
            
            while (indice < len) {
                if (S[indice] == 'X') {
                    S[indice] = 'O'; //se tava acesa, apaga
                    break;
                } else if (S[indice] == 'O') {
                    S[indice] = 'X'; //se tava apagada, acende
                    indice++; //vai prox led
                }
            }
        }
        
        //printa o estado final
        printf("%s\n", S);
        
        //coloca os simbolos entre aas luzes
        if (i == 0) {
            strcpy(luz_gigante, S); //primeira vez, s� copia com strcpy
        } else {
            int tamanho_atual = strlen(luz_gigante); //pega o tamanho atual da luz gigante
            char ultimo_led = luz_gigante[tamanho_atual - 1]; //pega o ultimo led da luz gigante
            char primeiro_led = S[0]; //pega o primeiro led do novo fio
            
            char simbolo[2]; //string para o simbolo entre os fios
            
            if (tamanho_atual % 2 == 0) { //se o n�mero de fios for par
                if (ultimo_led == primeiro_led) {
                    simbolo[0] = '@'; //se o ultimo for igual ao primeiro
                } else {
                    simbolo[0] = '$'; //se o ultimo for diferente do primeiro
                }
            } else {                      
                if (ultimo_led == primeiro_led) {
                    simbolo[0] = '#'; //se o ultimo for igual ao primeiro
                } else {
                    simbolo[0] = '%'; //se o ultimo for diferente do primeiro
                }
            }
            simbolo[1] = '\0'; 
            
            strcat(luz_gigante, simbolo); //coloca o simbolo
            strcat(luz_gigante, S); //coloca a nova string do fio
        }
    }
    
    //printa tudo junto
    printf("%s\n", luz_gigante);
    
    return 0;
}