/*
    Teste Tecnico - Desenvolvedor(a) de Sistemas Embarcados
    Arthur Lima de Castro
    Salvus - Julho de 2024
*/

// --------------- Importacoes de bibiotecas ---------------
#include <stdio.h>
#include <stdlib.h>
#include "lib/pagamento.c"


// --------------- Macros ---------------
#define BONUS_FIXO_EM_REAIS     200.00      // Considerando um valor de comissao por contrato igual para todos os funcionarios


// --------------- Funcao principal ---------------
int main(void) {
    // Criando primeiro item da lista encadeada com as folhas individuais
    FolhaDePagamentoIndividual_t *ptr_primeiro_registro = NULL;

    ptr_primeiro_registro = (FolhaDePagamentoIndividual_t *) malloc(sizeof(FolhaDePagamentoIndividual_t));
    if (ptr_primeiro_registro == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }
    strcpy(ptr_primeiro_registro->nome_do_funcionario, "Joao");
    ptr_primeiro_registro->qtd_de_contratos = 0;
    ptr_primeiro_registro->bonus_por_contrato = BONUS_FIXO_EM_REAIS;
    ptr_primeiro_registro->tipo_de_vinculo = terceirizacao;
    ptr_primeiro_registro->dados_do_vinculo.terceirizado.taxa_por_hora = 50.00;
    ptr_primeiro_registro->dados_do_vinculo.terceirizado.horas_trabalhadas = 100.0;
    ptr_primeiro_registro->func = calcular_folha_individual;
    ptr_primeiro_registro->proximo_registro = NULL;

    // 1) Cadastrando as informacoes do mes para cada funcionario:
    /* Cada chamada a 'cadastrar_folha_clt' ou a 'cadastrar_folha_terceirizado' adiciona um registro em uma lista encadeada, alocando memoria conforme necessario */
    // cadastrar_folha_terceirizado(ptr_primeiro_registro, "Joao", 50.00, 100.0, 0, BONUS_FIXO_EM_REAIS);
    cadastrar_folha_clt(ptr_primeiro_registro, "Marcela", 3000.00, 10, BONUS_FIXO_EM_REAIS);
    cadastrar_folha_terceirizado(ptr_primeiro_registro, "Joaquim", 30.00, 180.0, 12, BONUS_FIXO_EM_REAIS);

    // 2) Exemplificando uma maneira de listar todas as informacoes cadastradas e os pagamentos individuais por funcionario:
    visualizar_folhas(ptr_primeiro_registro);

    // 3) Calculando o total da folha de pagamento da empresa:
    printf("\nFolha de Pagamento Total da SmartWork: R$ %.2f\n\n", calcular_folha_total(ptr_primeiro_registro));

    liberar_memoria(ptr_primeiro_registro);
    return 0;
}
