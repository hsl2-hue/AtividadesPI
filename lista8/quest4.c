#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 1000
#define MAX_INCONSISTENCIAS 2000

// Estrutura para o Arquivo Mestre de Produtos
typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    double preco;
} Produto;

// Estrutura para ler o Arquivo de Movimentos
typedef struct {
    int codigo;
    char tipo;
    int quantidade;
} Movimento;

// Estrutura auxiliar para armazenar as Inconsistências temporariamente
typedef struct {
    int codigo;
    char tipo;
    int quantidade;
    char motivo[30];
} Inconsistencia;

int main() {
    // [Tratamento de Erro]: Validação de abertura dos arquivos de entrada
    FILE *f_prod = fopen("produtos.txt", "r");
    FILE *f_mov = fopen("movimentos.txt", "r");

    if (f_prod == NULL || f_mov == NULL) {
        if (f_prod) fclose(f_prod);
        if (f_mov) fclose(f_mov);
        return 1;
    }

    Produto produtos[MAX_PRODUTOS];
    int total_produtos = 0;

    //Leitura do arquivo mestre para a memória
    while (fscanf(f_prod, "%d %s %d %lf", 
                  &produtos[total_produtos].codigo, 
                  produtos[total_produtos].nome, 
                  &produtos[total_produtos].quantidade, 
                  &produtos[total_produtos].preco) == 4) {
        total_produtos++;
        if (total_produtos >= MAX_PRODUTOS) break;
    }
    fclose(f_prod); // Fecha o arquivo mestre logo após o carregamento

    // Variáveis e contadores para o relatório estatístico
    int movimentos_aplicados = 0;
    int saidas_recusadas = 0;
    int movimentos_sem_cadastro = 0;

    Inconsistencia inconsistencias[MAX_INCONSISTENCIAS];
    int total_inconsistencias = 0;

    Movimento mov;

    // 2. Processamento do arquivo de movimentos linha por linha (Em paralelo lógico)
    while (fscanf(f_mov, "%d %c %d", &mov.codigo, &mov.tipo, &mov.quantidade) == 3) {
        int encontrado = 0;
        int idx = -1;

        // Busca o produto correspondente no array em memória
        for (int i = 0; i < total_produtos; i++) {
            if (produtos[i].codigo == mov.codigo) {
                encontrado = 1;
                idx = i;
                break;
            }
        }

        if (!encontrado) {
            // Regra: Movimentos com código inexistente em produtos.txt
            movimentos_sem_cadastro++;
            if (total_inconsistencias < MAX_INCONSISTENCIAS) {
                inconsistencias[total_inconsistencias].codigo = mov.codigo;
                inconsistencias[total_inconsistencias].tipo = mov.tipo;
                inconsistencias[total_inconsistencias].quantidade = mov.quantidade;
                strcpy(inconsistencias[total_inconsistencias].motivo, "PRODUTO_INEXISTENTE");
                total_inconsistencias++;
            }
        } else {
            // Processamento de acordo com o Tipo (E / S)
            if (mov.tipo == 'E') {
                produtos[idx].quantidade += mov.quantidade;
                movimentos_aplicados++;
            } else if (mov.tipo == 'S') {
                // Regra: Tipo S só subtrai se houver estoque suficiente
                if (produtos[idx].quantidade >= mov.quantidade) {
                    produtos[idx].quantidade -= mov.quantidade;
                    movimentos_aplicados++;
                } else {
                    // Saída recusada (Estoque insuficiente)
                    saidas_recusadas++;
                    if (total_inconsistencias < MAX_INCONSISTENCIAS) {
                        inconsistencias[total_inconsistencias].codigo = mov.codigo;
                        inconsistencias[total_inconsistencias].tipo = mov.tipo;
                        inconsistencias[total_inconsistencias].quantidade = mov.quantidade;
                        strcpy(inconsistencias[total_inconsistencias].motivo, "ESTOQUE_INSUFICIENTE");
                        total_inconsistencias++;
                    }
                }
            }
        }
    }
    fclose(f_mov); // Fecha o arquivo de movimentos

    // 3. Geração do arquivo "estoque_atualizado.txt" (Mantendo a ordem mestre original)
    FILE *f_est_atualizado = fopen("estoque_atualizado.txt", "w");
    if (f_est_atualizado == NULL) {
        return 1;
    }

    for (int i = 0; i < total_produtos; i++) {
        fprintf(f_est_atualizado, "%d %s %d %.2f\n", 
                produtos[i].codigo, 
                produtos[i].nome, 
                produtos[i].quantidade, 
                produtos[i].preco);
    }
    fclose(f_est_atualizado);

    // 4. Geração do arquivo "relatorio.txt" conforme a especificação de saída
    FILE *f_relatorio = fopen("relatorio.txt", "w");
    if (f_relatorio == NULL) {
        return 1;
    }

    fprintf(f_relatorio, "PRODUTOS PROCESSADOS: %d\n", total_produtos);
    fprintf(f_relatorio, "MOVIMENTOS APLICADOS: %d\n", movimentos_aplicados);
    fprintf(f_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(f_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", movimentos_sem_cadastro);

    // Seção de Estoque Baixo (quantidade <= 5)
    fprintf(f_relatorio, "ESTOQUE BAIXO:\n");
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].quantidade <= 5) {
            fprintf(f_relatorio, "%d %s %d\n", produtos[i].codigo, produtos[i].nome, produtos[i].quantidade);
        }
    }

    // Seção de Inconsistências mapeadas
    fprintf(f_relatorio, "INCONSISTENCIAS:\n");
    for (int i = 0; i < total_inconsistencias; i++) {
        fprintf(f_relatorio, "%d %c %d %s\n", 
                inconsistencias[i].codigo, 
                inconsistencias[i].tipo, 
                inconsistencias[i].quantidade, 
                inconsistencias[i].motivo);
    }
    fclose(f_relatorio);

    return 0;
}