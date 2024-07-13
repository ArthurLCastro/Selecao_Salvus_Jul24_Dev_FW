/*
    Teste Tecnico - Desenvolvedor(a) de Sistemas Embarcados
    Arthur Lima de Castro
    Salvus - Julho de 2024
*/

// --------------- Importacoes de bibiotecas ---------------
#include <stdio.h>
#include <stdlib.h>
#include "lib/pagamento.c"


// --------------- Funcao principal ---------------
int main(void) {

    // 1) Cadastrando as informacoes do mes para cada funcionario:
    InfoMensalPorFuncionario registros[] = {
        cadastrar_info_mensal_terceirizado("Joao", 50.00, 100.0, 0),
        cadastrar_info_mensal_clt("Marcela", 3000.00, 10),
        cadastrar_info_mensal_terceirizado("Joaquim", 30.00, 180.0, 12),
        // ... Registros de outros funcionarios podem ser cadastrados aqui
    };

    int qtd_registros = sizeof(registros)/sizeof(registros[0]);

    // 2) Exemplificando uma maneira de listar todas as informacoes cadastradas e os pagamentos individuais por funcionario:
    for (int idx=0; idx<qtd_registros; idx++) {
        imprimir_info_mensal(registros[idx]);        
        printf("\tPagamento de %s: R$ %.2f\n\n", registros[idx].nome_do_funcionario, calcular_pagamento_individual(registros[idx]));
    }

    // 3) Calculando o total da folha de pagamento da empresa:
    float folha_total = calcular_folha_de_pagamento_total(registros, qtd_registros);
    printf("\nFolha de Pagamento Total da SmartWork: R$ %.2f\n\n", folha_total);

    return 0;
}
