#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    // Função Modular: deve ser atribuída conforme o tipo do sistema.
    // m: ponteiro para o mecha dono do sistema.
    // slot: o índice da posição de entrada deste sistema no array sistemas[]
    // input: o dano base enviado pelo Wintermute para o combate.
    // output: onde deve ser gravado o resultado final da operação.
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};

// lógica de combate
void rotina_defesa(Mecha *m, int slot, int input, int *output){
    int dano = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if(dano < 0){
        dano = 0;
    }
    *output = dano;
}

void rotina_utilidade(Mecha *m, int slot, int input, int *output){
    int recuperacao = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += recuperacao;
    *output = recuperacao;
}

void rotina_ataque(Mecha *m, int slot, int input, int *output){
    if(m->energia_atual < m ->sistemas[slot].atrib2){
        *output = 0; // Falha por falta de energia
    } else {
        int dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2; // Custo de energia
        *output = dano;
    }
}

int main(){
    int N; //quantidade de mechas
    scanf("%d", &N);

    Mecha **esquadrao = (Mecha **)malloc(N * sizeof(Mecha *)); //array de ponteiros para mechas
    
    for(int i = 0; i < N; i++){
        int ID, energia_inicial, Q;
        char modelo[30];
        scanf("%d %s %d %d", &ID, modelo, &energia_inicial, &Q);

        Mecha *novo_mecha = (Mecha *)malloc(sizeof(Mecha) + Q * sizeof(SubSistema));
        novo_mecha->id = ID;
        strcpy(novo_mecha->modelo, modelo);
        novo_mecha->energia_atual = energia_inicial;
        novo_mecha->num_sistemas = Q;

        for(int j = 0; j < Q; j++){
            char tipo; //A, D ou U
            
            scanf(" %c %s %d %d", &tipo, novo_mecha->sistemas[j].nome, &novo_mecha->sistemas[j].atrib1, &novo_mecha->sistemas[j].atrib2);

            if(tipo == 'D'){
                novo_mecha->sistemas[j].subrotina = rotina_defesa;
            } else if(tipo == 'U'){
                novo_mecha->sistemas[j].subrotina = rotina_utilidade;
            } else if(tipo == 'A'){
                novo_mecha->sistemas[j].subrotina = rotina_ataque;
            }
        }
        scanf("%d", &novo_mecha->valor_wintermute);
        esquadrao[i] = novo_mecha; //adiciona o mecha ao esquadrão
    }

    //ordenação por ID usando Bubble Sort
    for(int i = 0; i < N-1; i++){
        for(int j = 0; j < N-i-1; j++){
            if(esquadrao[j]->id > esquadrao[j+1]->id){
                Mecha *temp = esquadrao[j];
                esquadrao[j] = esquadrao[j+1];
                esquadrao[j+1] = temp;
            }
        }
    }

    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for(int i = 0; i < N; i++){
        Mecha *m = esquadrao[i];
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        int output_resultado = 0;

        //prioridade defesa
        for(int s = 0; s < m->num_sistemas; s++){
            if(m->sistemas[s].subrotina == rotina_defesa){
                m->sistemas[s].subrotina(m, s, m->valor_wintermute, &output_resultado);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[s].nome, output_resultado);
            }
        }

        //utilidade
        for(int s = 0; s < m->num_sistemas; s++){
            if(m->sistemas[s].subrotina == rotina_utilidade){
                m->sistemas[s].subrotina(m, s, m->valor_wintermute, &output_resultado);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[s].nome, m->energia_atual);
            }
        }

        for(int s = 0; s < m->num_sistemas; s++){
            if(m->sistemas[s].subrotina == rotina_ataque){
                m->sistemas[s].subrotina(m, s, m->valor_wintermute, &output_resultado);

                if(output_resultado == 0 && m->energia_atual < m->sistemas[s].atrib2){
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[s].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[s].nome, output_resultado, m->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
    }
    printf("Esquadrao pronto para o combate.\n");

    //limpeza de memória
    for(int i = 0; i < N; i++){
        free(esquadrao[i]);
    }
    free(esquadrao);

    return 0;
}