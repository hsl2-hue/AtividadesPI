#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*Aqui definimos o Nó. Cada aluno na fila é um nó contendo seus dados e um "gancho" (proximo)
apontando para o aluno que está atrás dele.*/
typedef struct Node{
    char matricula[12]; // matricula do aluno 
    int prioridade; // prioridade do aluno
    double cr; // coeficiente de rendimento
    long long L; // tempo de chegada do aluno na fila
    long long R; // tempo limite
    struct Node* proximo; // ponteiro para o próximo aluno da fila
} Node;

/*A Fila gerencia o fluxo guardando onde ela começa (para remover) e 
onde ela termina (para inserir novos alunos rapidamente).*/
typedef struct {
    Node* incio; //ponteiro para o primeiro aluno da fila
    Node* fim; //ponteiro para o último aluno da fila
} Fila;

void inicializar(Fila* fila){
    // inicio e fim começam zerados
    fila->incio = NULL;
    fila->fim = NULL;
}

int vazia(Fila* fila){
    return fila->incio == NULL; // A fila é vazia se o início for NULL
}

//enfileirar
void enqueue(Fila* fila, Node* novo){
    novo->proximo = NULL; // como sera o ultimo nó, n tem niguem depois
    if(vazia(fila)){
        // se ta vazia, o novo aluno é o inicio e o fim
        fila->incio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo; //o antigo ultimo da fila agr aponta para o novo aluno
        fila->fim = novo; //atualizo o ponteiro do fim para ser o novo aluno
    }
}

//desenfileirar, tira da frente
Node* dequeue(Fila* fila){
    if(vazia(fila)){
        //se n tiver ninguém, n tem oq remover
        return NULL;
    }

    Node* temp = fila->incio; //guarda o primeiro aluno temporariamente
    fila->incio = fila->incio->proximo; // o inicio passa a ser o segundo aluno

    if(fila->incio == NULL){
        //se ao remover, a fila esvaziou ent o fim tmb esvazia
        fila->fim = NULL;
    }
    return temp;
}

int main(){
    char comando[10]; //comando lido (START, ADD, PROC, FIM)
    char disciplina[55];
    int vagas; //vagas disponíveis

    Fila requisicoes;
    Fila confirmados;
    long long tempo_servidor = -1;

    while(scanf("%s", comando) != EOF){
        
        if(strcmp(comando, "START")==0){
            scanf("%s %d", disciplina, &vagas);
            //zera as filas
            inicializar(&requisicoes);
            inicializar(&confirmados);
            //reseta o relógio
            tempo_servidor = 1; 
        } else if(strcmp(comando, "ADD")==0) {
            Node* n = (Node*)malloc(sizeof(Node)); //cria um espaço para um novo aluno
            scanf("%s %d %lf %lld %lld", n->matricula, &n->prioridade, &n->cr, &n->L, &n->R);
            enqueue(&requisicoes, n); //coloca no fial da fila
        } else if(strcmp(comando, "PROC")==0){
            int quantidade;
            scanf("%d", &quantidade); //le quantos alunos deve processar agr

            for(int i = 0; i< quantidade; i++){
                if(vazia(&requisicoes)){
                    break;
                }

                //tira o primeiro aluno da fila
                Node* n = dequeue(&requisicoes);

                if(tempo_servidor < n->L){
                    tempo_servidor = n->L;
                }

                // caso passe o tempo limite
                if(tempo_servidor == 0){
                    printf("[TIMEOUT] mat=%s | Desconectado da fila.\n", n->matricula);
                    free(n);
                } else {
                    //calcula a pontuação
                    int score = (int)(round(n->cr * 100.00))/n->cr;

                    if(vagas > 0){
                        printf("[ALOCADO] mat=%s | score=%d | Processado no seg: %lld\n", n->matricula, score, tempo_servidor);
                        enqueue(&confirmados, n); //move para a lista de confirmados
                        vagas--;
                        tempo_servidor++;
                    } else {
                        printf("[LOTADO] mat=%s | score=%d | Processado no seg: %lld\n", n->matricula, score, tempo_servidor);
                        free(n);
                        tempo_servidor++;
                    }
                }
            }
        } else if(strcmp(comando, "FIM")==0){
            printf("--- LISTA OFICIAL: %s ---\n", disciplina);
            int posicao = 1;

            //enquanto houver confirmados
            while(!vazia(&confirmados)){
                Node* n = dequeue(&confirmados); //tira da fila
                printf("%d. Matricula: %s\n", posicao++, n->matricula);
                free(n);
            }

            //linpa oq sobrou
            while(!vazia(&requisicoes)){
                Node* n = dequeue(&requisicoes);
                free(n);
            }
        }
    }

    return 0;
}