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
    // Inicializando lista encadeada de itens que conterao a folha individual e um ponteiro para o proximo item
    Item_t head;
    head.prox = NULL;

    // 1) Criando folha de um funcionario e a inserindo ao final de uma lista encadeada (que inicia em 'head' e aloca memoria dinamicamente):
    insere_na_lista(&head, criar_folha_individual_terceirizado("Joao", 50.00, 100.0, 0, BONUS_FIXO_EM_REAIS));
    insere_na_lista(&head, criar_folha_individual_clt("Marcela", 3000.0, 10, BONUS_FIXO_EM_REAIS));
    insere_na_lista(&head, criar_folha_individual_terceirizado("Joaquim", 30.00, 180.0, 12, BONUS_FIXO_EM_REAIS));

    // 2) Exemplificando uma maneira de listar todas as folhas individuais cadastradas e os pagamentos por funcionario:
    imprimir_folhas(&head);

    // 3) Calculando o total da folha de pagamento da empresa:
    printf("\nFolha de Pagamento Total da SmartWork: R$ %.2f\n\n", calcular_folha_total(&head));

    liberar_memoria(&head);
    return 0;
}
