#include "pagamento.h"
#include <string.h>

void cadastrar_folha_clt(FolhaDePagamentoIndividual_t *ptr_primeiro_registro, char nome_do_funcionario[], float salario_fixo_mensal, int qtd_de_contratos, float bonus_por_contrato) {
    FolhaDePagamentoIndividual_t *registro_atual = ptr_primeiro_registro;

    // Percorrendo lista ate encontrar o ultimo registro
    while (registro_atual->proximo_registro != NULL) {
        registro_atual = registro_atual->proximo_registro;
    }

    // Adicionando dados ao novo registro
    registro_atual->proximo_registro = (FolhaDePagamentoIndividual_t *) malloc(sizeof(FolhaDePagamentoIndividual_t));

    strcpy(registro_atual->proximo_registro->nome_do_funcionario, nome_do_funcionario);
    registro_atual->proximo_registro->qtd_de_contratos = qtd_de_contratos;
    registro_atual->proximo_registro->bonus_por_contrato = bonus_por_contrato;

    // Dados especificos para funcionario celetista
    registro_atual->proximo_registro->tipo_de_vinculo = clt;
    registro_atual->proximo_registro->dados_do_vinculo.celetista.salario_fixo_mensal = salario_fixo_mensal;
    
    registro_atual->proximo_registro->func = calcular_folha_individual;
    registro_atual->proximo_registro->proximo_registro = NULL;
}

void cadastrar_folha_terceirizado(FolhaDePagamentoIndividual_t *ptr_primeiro_registro, char nome_do_funcionario[], float taxa_por_hora, float horas_trabalhadas, int qtd_de_contratos, float bonus_por_contrato) {
    FolhaDePagamentoIndividual_t *registro_atual = ptr_primeiro_registro;

    // Percorrendo lista ate encontrar o ultimo registro
    while (registro_atual->proximo_registro != NULL) {
        registro_atual = registro_atual->proximo_registro;
    }

    // Adicionando dados ao novo registro
    registro_atual->proximo_registro = (FolhaDePagamentoIndividual_t *) malloc(sizeof(FolhaDePagamentoIndividual_t));

    strcpy(registro_atual->proximo_registro->nome_do_funcionario, nome_do_funcionario);
    registro_atual->proximo_registro->qtd_de_contratos = qtd_de_contratos;
    registro_atual->proximo_registro->bonus_por_contrato = bonus_por_contrato;

    // Dados especificos para funcionario terceirizado
    registro_atual->proximo_registro->tipo_de_vinculo = terceirizacao;
    registro_atual->proximo_registro->dados_do_vinculo.terceirizado.taxa_por_hora = taxa_por_hora;
    registro_atual->proximo_registro->dados_do_vinculo.terceirizado.horas_trabalhadas = horas_trabalhadas;

    registro_atual->proximo_registro->func = calcular_folha_individual;
    registro_atual->proximo_registro->proximo_registro = NULL;
}

float calcular_folha_individual(FolhaDePagamentoIndividual_t* ptr_primeiro_registro) {
    if (ptr_primeiro_registro == NULL) return 0;

    float pagamento_base = 0, bonus = 0;

    if (ptr_primeiro_registro->tipo_de_vinculo == clt) {
        pagamento_base = ptr_primeiro_registro->dados_do_vinculo.celetista.salario_fixo_mensal;
    } else if (ptr_primeiro_registro->tipo_de_vinculo == terceirizacao) {
        pagamento_base = ptr_primeiro_registro->dados_do_vinculo.terceirizado.taxa_por_hora * ptr_primeiro_registro->dados_do_vinculo.terceirizado.horas_trabalhadas;
    }

    bonus = ptr_primeiro_registro->qtd_de_contratos * ptr_primeiro_registro->bonus_por_contrato;

    return pagamento_base + bonus;
}

void visualizar_folhas(FolhaDePagamentoIndividual_t *ptr_primeiro_registro) {
    FolhaDePagamentoIndividual_t *registro_atual = ptr_primeiro_registro;

    while (registro_atual != NULL) {
        printf("\xAF %s:\n", registro_atual->nome_do_funcionario);

        printf("\tTipo de contrata\x87\xc6o: ");
        if (registro_atual->tipo_de_vinculo == clt) {
            printf("CLT\n");
        
            printf("\tSal\xA0rio fixo mensal: R$ %.2f\n", registro_atual->dados_do_vinculo.celetista.salario_fixo_mensal);
        } else if (registro_atual->tipo_de_vinculo == terceirizacao) {
            printf("Terceirizado\n");

            printf("\tValor por hora trabalhada: R$ %.2f\n", registro_atual->dados_do_vinculo.terceirizado.taxa_por_hora);
            printf("\tHoras trabalhadas no m\x88s: %.2f h\n", registro_atual->dados_do_vinculo.terceirizado.horas_trabalhadas);
        } else {
            printf("\t[Erro] Tipo de contrata\x87\xc6o inv\xA0lida!\n");
        }

        printf("\tTaxa por contrato assinado: %.2f\n", registro_atual->bonus_por_contrato);
        printf("\tQuantidade de contratos assinados no m\x88s: %i\n", registro_atual->qtd_de_contratos);
    
        float pagamento = registro_atual->func(registro_atual);
        printf("\tPagamento de %s: R$ %.2f\n\n", registro_atual->nome_do_funcionario, pagamento);

        registro_atual = registro_atual->proximo_registro;
    }
}

float calcular_folha_total(FolhaDePagamentoIndividual_t *ptr_primeiro_registro) {
    FolhaDePagamentoIndividual_t *registro_atual = ptr_primeiro_registro;

    float total = 0;

    while (registro_atual != NULL) {
        total += registro_atual->func(registro_atual);

        registro_atual = registro_atual->proximo_registro;
    }

    return total;
}

void liberar_memoria(FolhaDePagamentoIndividual_t* ptr_primeiro_registro) {
    FolhaDePagamentoIndividual_t *registro_atual = ptr_primeiro_registro;
    FolhaDePagamentoIndividual_t *proximo;

    while (registro_atual != NULL) {
        proximo = registro_atual->proximo_registro;
        free(registro_atual);
        registro_atual = proximo;
    }
}
