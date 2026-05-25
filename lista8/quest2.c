#include <stdio.h>
#include <stdint.h> // Para usar uint32_t
#include <stdlib.h>

//uint32_t são inteiros de 32 bits sem sinal
//int32_t são inteiros de 32 bits com sinal

typedef union {
    uint32_t raw;

    struct {
        uint32_t ID_sensor : 10;
        uint32_t status : 3;
        uint32_t bateria : 1;
        int32_t temperatura : 12;
        uint32_t controle : 6;
    } campos;
} PacoteRecebido;

int main() {
    uint32_t dado_recebido;
    int capacidade = 2;
    int quantidade = 0;

    PacoteRecebido *historico = malloc(capacidade * sizeof(PacoteRecebido));
    if(historico == NULL) {
        return 1;
    }
    
    //x para ler em formato hexadecimal
    while(scanf("%x", &dado_recebido) == 1) {
        if(dado_recebido == 0) {
            break; // Encerra a leitura se o valor for 0
        }

        if(quantidade >= capacidade){
            capacidade *= 2;
            // Realoca o array para a nova capacidade
            PacoteRecebido *novo_historico = realloc(historico, capacidade * sizeof(PacoteRecebido));
            if(novo_historico == NULL) {
                free(historico);
                return 1;
            }
            historico = novo_historico;
        }
        historico[quantidade].raw = dado_recebido;
        quantidade++;
    }

    for(int i = 0; i < quantidade; i++){
        printf("Pacote[%d] - Dado Bruto: %#010X\n", i + 1, historico[i].raw);
        printf("ID do Sensor : %u\n", historico[i].campos.ID_sensor);
        printf("Status : %u\n", historico[i].campos.status);
        if(historico[i].campos.bateria == 0){
            printf("Bateria Baixa: Nao\n");
        } else {
            printf("Bateria Baixa: SIM (ALERTA)\n");
        }
        printf("Temperatura : %d graus\n", historico[i].campos.temperatura);
        printf("-------------------------------------------------\n");
    }
    
    free(historico);
    return 0;
}