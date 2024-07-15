#ifndef PAGAMENTO_H
#define PAGAMENTO_H


// --------------- Estruturas ---------------
enum vinculo_empregaticio { 
    clt,
    terceirizacao
};

union dados_empregaticios {
    struct {
        float salario_fixo_mensal;
    } celetista;
    struct {
        float taxa_por_hora;
        float horas_trabalhadas;
    } terceirizado;
};

typedef struct {
    char nome_do_funcionario[50];
    enum vinculo_empregaticio tipo_de_vinculo;
    union dados_empregaticios dados_do_vinculo;
    int qtd_de_contratos;
    float bonus_por_contrato;
} InfoMensalPorFuncionario;


// --------------- Funcoes ---------------
InfoMensalPorFuncionario cadastrar_info_mensal_clt(char nome_do_funcionario[], float salario_fixo_mensal, int qtd_de_contratos, float bonus_por_contrato);
InfoMensalPorFuncionario cadastrar_info_mensal_terceirizado(char nome_do_funcionario[], float taxa_por_hora, float horas_trabalhadas, int qtd_de_contratos, float bonus_por_contrato);
void imprimir_info_mensal(InfoMensalPorFuncionario registro);
float calcular_pagamento_individual(InfoMensalPorFuncionario registro);
float calcular_folha_de_pagamento_total(InfoMensalPorFuncionario *registros, int qtd_registros);

#endif