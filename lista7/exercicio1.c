#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titulo[50];
    char genero[30];
    char studio[30];
    char console[30];
    int nota;
    int ano;
} Jogo;

//função para imprimir os títulos dos jogos lançados em um determinado ano
void printAno(Jogo jogos[], int n, int ano){
    int contador = 0;
    for(int i = 0; i < n; i++){
        if(jogos[i].ano == ano){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }

    if (contador > 0) {
        printf("Tenho %d jogos || %d.\n", contador, ano);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

//função para imprimir os títulos dos jogos que começam com uma determinada letra
void printLetra(Jogo jogos[], int n, char letra){
    int contador = 0;
    for(int i = 0; i < n; i++){
        if(jogos[i].titulo[0] == letra){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }
    if (contador > 0) {
        printf("Tenho %d jogos || %c.\n", contador, letra);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

//função para imprimir os títulos dos jogos de um determinado estúdio
void printStudio(Jogo jogos[], int n, char studio[]){
    int contador = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(jogos[i].studio, studio) == 0){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }

    if (contador > 0) {
        printf("Tenho %d jogos || %s.\n", contador, studio);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

//função para imprimir os títulos dos jogos de um determinado console
void printConsole(Jogo jogos[], int n, char console[]){
    int contador = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(jogos[i].console, console) == 0){
            printf("%s\n", jogos[i].titulo);
            contador++;
        }
    }

    if (contador > 0) {
        printf("Tenho %d jogos || %s.\n", contador, console);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

//imprime toda a coleção
void printColecao(Jogo jogos[], int n){
    for(int i = 0; i < n; i++){
        printf("%s %d\n", jogos[i].titulo, jogos[i].nota);
    }
}

int main(){
    int n; 
    scanf("%d", &n);

    Jogo listaJogos[100];
    //Cria um espaço na memória para 100 elementos, onde cada um deles segue o molde do tipo Jogo
    
    for(int i = 0; i < n; i++){
        scanf("%s %s %s %s %d %d",
              listaJogos[i].titulo,
              listaJogos[i].genero,
              listaJogos[i].studio,
              listaJogos[i].console,
              &listaJogos[i].nota,
              &listaJogos[i].ano);
        
        if(listaJogos[i].nota > 7){
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        } else if(listaJogos[i].nota < 4){
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }


    char comando[30];
    while(scanf("%s", comando) != EOF){
        if(strcmp(comando, "printAno") == 0){
            int ano_procurado;
            scanf("%d", &ano_procurado);
            printAno(listaJogos, n, ano_procurado);
        } else if(strcmp(comando, "printLetra") == 0){
            char letra_procurada;
            scanf(" %c", &letra_procurada);
            printLetra(listaJogos, n, letra_procurada);
        } else if(strcmp(comando, "printStudio") == 0){
            char studio_procurado[30];
            scanf("%s", studio_procurado);
            printStudio(listaJogos, n, studio_procurado);
        } else if(strcmp(comando, "printConsole") == 0){
            char console_procurado[30];
            scanf("%s", console_procurado);
            printConsole(listaJogos, n, console_procurado);
        } else if(strcmp(comando, "printColecao") == 0){
            printColecao(listaJogos, n);
        }
    }

    printf("Enjoei de jogar, agora vou ver TV.\n");
    return 0;
}
