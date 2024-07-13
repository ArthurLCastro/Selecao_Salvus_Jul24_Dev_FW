#ifndef PAGAMENTO_H
#define PAGAMENTO_H


// --------------- Macros ---------------
#define BONUS_FIXO_EM_REAIS     200.00      // Considerando um valor de comissao por contrato geral para todos os funcionarios


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
        float valor_por_hora_trabalhada;
        float horas_trabalhadas_no_mes;
    } terceirizado;
};

typedef struct {
    char nome_do_funcionario[50];
    enum vinculo_empregaticio tipo_de_vinculo;
    union dados_empregaticios dados_do_vinculo;
    int qtd_de_contratos;
} InfoMensalPorFuncionario;


// --------------- Funcoes ---------------
InfoMensalPorFuncionario cadastrar_info_mensal_clt(char nome_do_funcionario[], float salario_fixo_mensal, int qtd_de_contratos);
InfoMensalPorFuncionario cadastrar_info_mensal_terceirizado(char nome_do_funcionario[], float valor_por_hora_trabalhada, float horas_trabalhadas_no_mes, int qtd_de_contratos);
void imprimir_info_mensal(InfoMensalPorFuncionario registro);
float calcular_pagamento_individual(InfoMensalPorFuncionario registro);
float calcular_folha_de_pagamento_total(InfoMensalPorFuncionario *registros, int qtd_registros);

#endif