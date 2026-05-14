#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char nome[250];
    int populacao;
    char grauPerigo[250];
    char funcao[250];
} Cidadela;

void formatar_capitalizacao(char *str){
    if(str[0] == '\0') return; // string vazia

    str[0] = toupper((unsigned char)str[0]); // primeira letra maiúscula
    for(int i = 1; str[i] != '\0'; i++){
        str[i] = tolower((unsigned char)str[i]); // restante minusculo
    }
}

//função para ajudar a ordenar
int comparar(const void *a, const void *b){
    Cidadela *ca = (Cidadela *)a;
    Cidadela *cb = (Cidadela *)b;

    //primeira regra de ordenação
    if(ca->populacao != cb->populacao){
        return cb->populacao - ca->populacao; //ordem decrescente
    }

    //segunda regra de ordenção (empate)
    int perigoA = strlen(ca->grauPerigo);
    int perigoB = strlen(cb->grauPerigo);
    if(perigoA != perigoB){
        return perigoB - perigoA; //ordem decrescente
    }
    //terceira regra de ordenação (empate duplo)
    return strcmp(ca->nome, cb->nome); //ordem alfabética crescente
}

int main(){
    char linha[250];
    Cidadela cidadelas[300];

    int qtdCidadelas = 0;
    int chave = -1;

    //leitura até o EOF
    while(fgets(linha, sizeof(linha), stdin)){
        linha[strcspn(linha, "\n")] = '\0'; //remover o \n do final da string
        if(strlen(linha) == 0) continue;

        //verifica mensagem especial
        if(strchr(linha, '!') != NULL){
            char numero[250] = {0};
            int numIndex = 0;
            //extrai a chave da mensagem
            for(int i = 0; linha[i] != '\0'; i++){
                if(isdigit((unsigned char)linha[i])){
                    numero[numIndex++] = linha[i];
                }
            }
            if(numIndex > 0){
                chave = atoi(numero); //converte a chave para inteiro
            }
        } else {
            Cidadela cid = {0};
            char populacaoStr[250] = {0};
            int numIndex = 0, populacaoIndex = 0, grauIndex = 0, funcaoIndex = 0;

            for(int i = 0; linha[i] != '\0'; i++){
                unsigned char c = (unsigned char)linha[i];

                if(isupper(c)){
                    cid.nome[numIndex++] = c;
                }
                if(isdigit(c)){
                    populacaoStr[populacaoIndex++] = c;
                }
                if(c == '*'){
                    cid.grauPerigo[grauIndex++] = c;
                }
                if(i >= 2 && linha[i-2] == ' ' && linha[i-1] == ' ' && c != ' '){
                    cid.funcao[funcaoIndex++] = c;
                }
            }
            //converção e formatação
            if(populacaoIndex > 0){
                cid.populacao = atoi(populacaoStr);
            } else {
                cid.populacao = 0;
            }
            formatar_capitalizacao(cid.nome);
            formatar_capitalizacao(cid.funcao);
            cidadelas[qtdCidadelas++] = cid; //adiciona a cidadela ao array
        }
    }

    if(chave == -1 || chave < 1 || chave > qtdCidadelas){
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {
        qsort(cidadelas, qtdCidadelas, sizeof(Cidadela), comparar);
        Cidadela alvo = cidadelas[chave - 1];

        char *perigo_texto; //ponteiro temporário

        if(strlen(alvo.grauPerigo) > 0){
            perigo_texto = alvo.grauPerigo;
        } else {
            perigo_texto = "sem perigo";
        }

        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s.",
        alvo.nome, alvo.populacao, alvo.funcao, perigo_texto);

        //verificação condições de risco
        int condicao1 = (alvo.populacao >= 1000);
        int condicao2 = (strlen(alvo.grauPerigo) > 3);

        if(condicao1 && condicao2){
            printf(" Talvez seja melhor desistir...\n");
        } else if(condicao1){
            printf(" Um lugar denso, vai ser difícil achar ela.\n");
        } else if(condicao2){
            printf(" Vai ser complicado entrar lá.\n");
        }
    }

    return 0;
}