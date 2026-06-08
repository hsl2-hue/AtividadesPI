#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura basica do arvore
/* onde cada nó precisa gurdar 3 coisas
 1. um dado inteiro
 2. um ponteiro filho da esquerda
 3. um ponteiro filho da direita
*/
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;

/*Importante:
Raiz (Root): É o nó que fica no topo da árvore. Toda travessia ou busca começa por ele.
Folha (Leaf): É um nó que não tem nenhum filho (ambos os ponteiros esquerda e direita são NULL).
Pai e Filho: Se um nó A aponta para um nó B, A é o pai e B é o filho.
*/

// função para criação de um novo no
No* criarNo(int valor){
    No* novoNo = (No*)malloc(sizeof(No)); //aloca memória
    novoNo->valor = valor; // atribui valor
    novoNo->esquerda = NULL; // inicializa filhos como Nulos
    novoNo->direita = NULL;
    return novoNo;
}

// função de inserção (ignora repetidos)
No* inserir(No* raiz, int valor){
    //se a arvore/ou ramificação tiver vazia
    if(raiz == NULL){
        return criarNo(valor);
    }

    //se o valor for menor, insere na esquerda
    if(valor < raiz->valor){
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor){
        raiz->direita = inserir(raiz->direita, valor); // se for maior insere a direita
    }
    //se for igual ignora

    return raiz;
}

/* Como navegar pela árvore
Como a árvore não é uma linha reta, você não pode usar um simples loop for para passar por todos os elementos. 
Nós usamos recursão para visitar os nós. Existem três formas principais de fazer isso:
1. Pré-ordem (Pre-order): Visita a Raiz, depois a subárvore Esquerda, depois a Direita.
2. Em-ordem (In-order): Visita a subárvore Esquerda, depois a Raiz, depois a Direita. 
(Muito útil em Árvores Binárias de Busca, pois imprime os números em ordem crescente).
3. Pós-ordem (Post-order): Visita a subárvore Esquerda, depois a Direita, e por último a Raiz. 
(Muito útil para deletar a árvore inteira da memória).
*/

//funções de percurso
void preOrdem(No* raiz){
    //primeiro raiz, depois esquerda depois direita
    if(raiz != NULL){
        printf("%d ", raiz->valor); // 1º visita a raiz
        preOrdem(raiz->esquerda); // 2º desce pa esquerda
        preOrdem(raiz->direita); // 3º desce pa direita
    }
}

void emOrdem(No* raiz){
    //primeiro esquerda, depois raiz, depois direita
    if(raiz != NULL){
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }   
}

void posOrdem(No* raiz){
    //primeiro esquerda, depois direita, depois raiz
    if(raiz != NULL){
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

/*Nas funções recursivas de árvore binária, 
a ordem em que você coloca o printf (que representa a ação de "visitar" ou "ler" o nó) 
em relação às chamadas para os filhos é o que define o tipo de travessia.

Como a recursão empilha as tarefas na memória do computador, 
mudar a posição do printf muda o momento exato em que a impressão acontece.*/

//funções de estatísticas da arvore
int contarNos(No* raiz){
    if(raiz == NULL) return 0;
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

int contarFolhas(No* raiz){
    if(raiz == NULL) {
        return 0;
    }
    //se n tiver filhos, é uma folha
    if(raiz->esquerda == NULL && raiz->direita == NULL){
        return 1;
    }
    return contarFolhas(raiz->esquerda) + contarFolhas(raiz->direita);
}

int calcularAltura(No* raiz){
    if(raiz == NULL){
        return -1;
    }

    int alturaEsq = calcularAltura(raiz->esquerda);
    int alturaDir = calcularAltura(raiz->direita);

    //retorna a maior altura entre os filhos + 1 (contando o atual)
    if(alturaEsq > alturaDir){
        return alturaEsq + 1;
    } else {
        return alturaDir + 1;
    }
}

No* encontrarMenor(No* raiz){
    if(raiz == NULL){
        return NULL;
    }
    //fica o mais a esquerda
    while(raiz->esquerda != NULL){
        raiz = raiz->esquerda;
    }
    return raiz;
}

No* encontrarMaior(No* raiz){
    if(raiz == NULL){
        return NULL;
    }
    //fica o mais a direita
    while(raiz->direita != NULL){
        raiz = raiz->direita;
    }
    return raiz;
}

void liberarArvore(No* raiz){
    if(raiz != NULL){
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main(){
    No* raiz = NULL;
    int pontuacao;

    //leitura das pontuações
    while(1){
        scanf("%d", &pontuacao);
        if(pontuacao == -1){
            break;
        }
        raiz = inserir(raiz, pontuacao);
    }

    //exibe os resultados se a arvore n tiver vazia
    if(raiz != NULL){
        printf("PREORDEM: ");
        preOrdem(raiz);
        printf("\n");

        printf("EMORDEM: ");
        emOrdem(raiz);
        printf("\n");

        printf("POSORDEM: ");
        posOrdem(raiz);
        printf("\n");

        printf("NOS: %d\n", contarNos(raiz));
        printf("FOLHAS: %d\n", contarFolhas(raiz));
        printf("ALTURA: %d\n", calcularAltura(raiz));

        No* menor = encontrarMenor(raiz);
        No* maior = encontrarMaior(raiz);

        printf("MENOR: %d\n", menor->valor);
        printf("MAIOR: %d\n", maior->valor);
    } else {
        printf("ARVORE VAZIA\n");
    }
    
    liberarArvore(raiz);

    return 0;
}