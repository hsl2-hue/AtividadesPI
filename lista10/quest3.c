#include <stdio.h>
#include <stdlib.h>

typedef struct Tarefa{
    int id;
    int prioridade;
    struct Tarefa* proxima;
} Tarefa;

typedef struct{
    Tarefa* head; //aponta pro inicio da fila
    Tarefa* tail; // aponta pro fim
} Fila;

void inserir(Fila* fila, int id, int prioridade){
    Tarefa* nova = (Tarefa*)malloc(sizeof(Tarefa));
    nova->id = id;
    nova->prioridade = prioridade;
    nova->proxima = NULL;

    if(fila->tail == NULL){
        //se tiver vaizia, o nova passa a ser o inicio e o final da fila
        fila->head = nova;
        fila->tail = nova;
    } else {
        fila->tail->proxima = nova; //Pega a tarefa que atualmente está no fim da fila e diz que a próxima tarefa depois dela será a nova
        fila->tail = nova; // atualiza o fim da fila
    }
}

//remover uma tarefa do inicio da fila
void remover(Fila* fila){
    if(fila->head == NULL){
        printf("Fila vazia\n");
        return;
    }

    Tarefa* temp = fila->head;
    printf("Removida: id=%d prioridade=%d\n", temp->id, temp->prioridade);

    fila->head = fila->head->proxima; //o inicio passa a ser o prox

    if(fila->head == NULL){
        fila->tail = NULL;
    }

    free(temp);
}

void listar(Fila* fila){
    if(fila->head == NULL){
        printf("Fila vazia\n");
        return;
    }

    Tarefa* atual = fila->head;
    while(atual != NULL){
        printf("id=%d prioridade=%d\n", atual->id, atual->prioridade);
        atual = atual->proxima;
    }
}

int main(){
    Fila fila;
    fila.head = NULL;
    fila.tail = NULL;

    char comando;

    while(scanf(" %c", &comando) != EOF){
        if(comando == "I"){
            int id, prioridade;
            scanf("%d %d", &id, &prioridade);
            inserir(&fila, id, prioridade);
        } else if (comando == 'R'){
            remover(&fila);
        } else if (comando == 'L'){
            listar(&fila);
        } else if (comando == 'F'){
            break;
        }
    }

    while (fila.head != NULL) {
        Tarefa* temp = fila.head;
        fila.head = fila.head->proxima;
        free(temp);
    }

    return 0;
}