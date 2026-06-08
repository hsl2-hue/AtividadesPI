#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//lista encadeada
typedef struct Node{
    char cor;
    struct Node* proximo;
} Node;

//função para processar a pilha
void processarBloco(Node** topo, char bloco){
    while(1){
        if(*topo != NULL && (*topo)->proximo != NULL){
            if((*topo)->cor == bloco && (*topo)->proximo->cor == bloco){
                //Guarda nós q serão removidos
                Node* remover1 = *topo;
                Node* remover2 = (*topo)->proximo;

                *topo = remover2->proximo;

                free(remover1);
                free(remover2);
                return;
            }
        }

        if(*topo != NULL){
            char t = (*topo)->cor;
            if ((t == 'g' && bloco == 'b') || (t == 'b' && bloco == 'g')) {
                Node* remover = *topo;
                *topo = (*topo)->proximo; // Desempilha o topo
                free(remover);            // Libera a memória
                bloco = 'c';              // Transforma a cor
                continue;                 // Reinicia para checar cascatas
            }
            // vermelho(r) + azul(b) = magenta(m)
            if ((t == 'r' && bloco == 'b') || (t == 'b' && bloco == 'r')) {
                Node* remover = *topo;
                *topo = (*topo)->proximo;
                free(remover);
                bloco = 'm';
                continue;
            }
            // vermelho(r) + verde(g) = amarelo(y)
            if ((t == 'r' && bloco == 'g') || (t == 'g' && bloco == 'r')) {
                Node* remover = *topo;
                *topo = (*topo)->proximo;
                free(remover);
                bloco = 'y';
                continue;
            }
        }
        Node* novo_no = (Node*)malloc(sizeof(Node));
        novo_no->cor = bloco;
        novo_no->proximo = *topo;
        *topo = novo_no;
        break;
    }
}


int main(){
    //cores possíveis: vermelho(r), verde(g), azul(b), ciano(c), magenta(m), amarelo(y).
    Node* topo = NULL; //começa vazia
    char cor;
    
    // espaço em branco para ignorar o enter
    while(scanf(" %c", &cor) != EOF){
        //chamar a função para processar a pilha
        processarBloco(&topo, cor);

        if(topo == NULL){
            printf("Pilha vazia!\n");
        } else {
            //imprime a pilha do topo até a base
            Node* atual = topo;
            while(atual != NULL){
                printf("%c\n", atual->cor);
                atual = atual->proximo;
            } 
        }
        //pula linha extra após cada jogada
        printf("\n");
    }
    printf("Thank You So Much For Playing My Game!\n");

    //liberar memoria se sobrar peças
    while(topo != NULL){
        Node* remover = topo;
        topo = topo->proximo;
        free(remover);
    }
    return 0;
}
