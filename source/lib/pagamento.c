#include "pagamento.h"
#include <string.h>


InfoMensalPorFuncionario cadastrar_info_mensal_clt(char nome_do_funcionario[], float salario_fixo_mensal, int qtd_de_contratos, float bonus_por_contrato) {
    InfoMensalPorFuncionario registro;

    strcpy(registro.nome_do_funcionario, nome_do_funcionario);
    registro.qtd_de_contratos = qtd_de_contratos;
    registro.bonus_por_contrato = bonus_por_contrato;

    // Dados especificos para funcionario celetista
    registro.tipo_de_vinculo = clt;
    registro.dados_do_vinculo.celetista.salario_fixo_mensal = salario_fixo_mensal;

    return registro;
}

InfoMensalPorFuncionario cadastrar_info_mensal_terceirizado(char nome_do_funcionario[], float taxa_por_hora, float horas_trabalhadas, int qtd_de_contratos, float bonus_por_contrato) {
    InfoMensalPorFuncionario registro;

    strcpy(registro.nome_do_funcionario, nome_do_funcionario);
    registro.qtd_de_contratos = qtd_de_contratos;
    registro.bonus_por_contrato = bonus_por_contrato;

    // Dados especificos para funcionario terceirizado
    registro.tipo_de_vinculo = terceirizacao;
    registro.dados_do_vinculo.terceirizado.taxa_por_hora = taxa_por_hora;
    registro.dados_do_vinculo.terceirizado.horas_trabalhadas = horas_trabalhadas;

    return registro;
}

void imprimir_info_mensal(InfoMensalPorFuncionario registro) {
    printf("\xAF %s:\n", registro.nome_do_funcionario);

    printf("\tTipo de contrata\x87\xc6o: ");
    if (registro.tipo_de_vinculo == clt) {
        printf("CLT\n");
    
        printf("\tSal\xA0rio fixo mensal: R$ %.2f\n", registro.dados_do_vinculo.celetista.salario_fixo_mensal);
    } else if (registro.tipo_de_vinculo == terceirizacao) {
        printf("Terceirizado\n");

        printf("\tValor por hora trabalhada: R$ %.2f\n", registro.dados_do_vinculo.terceirizado.taxa_por_hora);
        printf("\tHoras trabalhadas no m\x88s: %.2f h\n", registro.dados_do_vinculo.terceirizado.horas_trabalhadas);
    } else {
        printf("\t[Erro] Tipo de contrata\x87\xc6o inv\xA0lida!\n");
    }

    printf("\tQuantidade de contratos assinados no m\x88s: %i\n", registro.qtd_de_contratos);
}

float calcular_pagamento_individual(InfoMensalPorFuncionario registro) {
    float pagamento_base = 0, bonus = 0;

    if (registro.tipo_de_vinculo == clt) {
        pagamento_base = registro.dados_do_vinculo.celetista.salario_fixo_mensal;
    } else if (registro.tipo_de_vinculo == terceirizacao) {
        pagamento_base = registro.dados_do_vinculo.terceirizado.taxa_por_hora * registro.dados_do_vinculo.terceirizado.horas_trabalhadas;
    }

    bonus = registro.qtd_de_contratos * registro.bonus_por_contrato;

    return pagamento_base + bonus;
}

float calcular_folha_de_pagamento_total(InfoMensalPorFuncionario *registros, int qtd_registros) {
    float total = 0;

    for (int idx=0; idx<qtd_registros; idx++) {
        float pagamento = calcular_pagamento_individual(registros[idx]);
        // printf("[%i]: %s (R$ %.2f)\n", idx, registros[idx].nome_do_funcionario, pagamento);
        total += pagamento;
    }

    return total;
}
