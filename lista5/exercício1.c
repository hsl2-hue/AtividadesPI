exercício1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//leitura de string dinamica
char* ler_string_dinamica() {
    int capacidade = 10; //começa com 10 de capacidade
    int tamanho = 0; //contador de letras lidas
    
    //pede um espaço na memória do tamanho de 10 letras
    char* str = (char*)malloc(capacidade * sizeof(char));
    
    char c; //guarda temporariamente a letra lida
    scanf(" %c", &c); //o espaço ignora enters acidentais
    
    do {
        str[tamanho++] = c; //armazena o caractere e incrementa o tamanho
        //verifica se é necessário aumentar a capacidade do array
        if (tamanho >= capacidade - 1) {
            capacidade *= 2; //dobra a capacidade
            
            //estica o tamanho para a nova capacidade
            char* ptr_temporario = (char*)realloc(str, capacidade * sizeof(char));
            if(ptr_temporario != NULL){
                str = ptr_temporario;
            } else {
                free(str);
                return NULL;
            }
            //boas práticas
        }
        
        c = getchar(); //lê a próxima letra
    } while (c != '\n' && c != '\r' && c != ' '); //continua ate q seja um desses
    
    str[tamanho] = '\0'; //adiciona o caractere de fim de string
    return str;
}

int main() {
    int n;
    
    // Lendo a quantidade de strings
    scanf("%d", &n);
    
    //array de ponteiros para armazenar as strings dinamicamente
    char *strings[n];
    
    int max_len = 0;//guarda o maior tamanho de letra lida
    int total_len = 0;//guarda o total de letras lidas

    for (int i = 0; i < n; i++) {
        strings[i] = ler_string_dinamica(); //chama a função e guarda no array
        if(strings[i] == NULL){
            printf("Erro de alocação\n");
            return 1;
        }


        int len_atual = strlen(strings[i]); //calcula o tamanho da string lida
        total_len += len_atual; //atualiza o total de letras lidas
        
        if (len_atual > max_len) {
            max_len = len_atual; //atualiza o maior tamanho se necessário
        }
    }
    
    //aloca o necessario juntar todas as letras em uma unica string
    char* merged_string = (char*)malloc((total_len + 1) * sizeof(char));
    int k = 0; 
    
    for (int col = 0; col < max_len; col++) {
        for (int lin = 0; lin < n; lin++) {
            if (col < strlen(strings[lin])) { //verifica se a palavra atual tem letra nessa coluna
                //pega a letra e adiciona na string final
                merged_string[k++] = strings[lin][col];
            }
        }
    }
    merged_string[k] = '\0'; //finaliza a string
    
    printf("%s\n", merged_string); 
    
    //fusão de letras iguais
    int i = 0;
    //percorre enquanto a letra atual e a próxima existirem
    while (merged_string[i] != '\0' && merged_string[i+1] != '\0') {
        //se a letra for igual a prox
        if (merged_string[i] == merged_string[i+1]) {
            
            if (merged_string[i] == 'z') {
                merged_string[i] = 'a';
            } else {
                merged_string[i] = merged_string[i] + 1; //transforma na prox letra
            }
            
            int j = i + 1;
            //puxa as letras da frente uma casa para trás, sobrescrevendo a letra repetida
            while (merged_string[j] != '\0') {
                merged_string[j] = merged_string[j+1];
                j++;
            }
            //decrementa o índice para verificar a nova letra na posição atual
            if (i > 0) {
                i--;
            }
        } else {
            i++; //avança se forem diferentes
        }
    }
    
    printf("%s\n", merged_string);
    
    //tudo q for alocado com malloc ou realloc deve ser liberado com free
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(merged_string);
    
    return 0;
}
