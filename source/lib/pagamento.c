#include "pagamento.h"
#include <string.h>


// --------------- Funcoes relacionadas as folhas de pagamento ---------------

FolhaDePagamentoIndividual_t criar_folha_individual_clt(char nome_do_funcionario[], float salario_fixo_mensal, int qtd_de_contratos, float bonus_por_contrato) {
    FolhaDePagamentoIndividual_t registro;

    strcpy(registro.nome_do_funcionario, nome_do_funcionario);
    registro.qtd_de_contratos = qtd_de_contratos;
    registro.bonus_por_contrato = bonus_por_contrato;

    registro.func = calcular_folha_individual;

    // Dados especificos para funcionario celetista
    registro.tipo_de_vinculo = clt;
    registro.dados_do_vinculo.celetista.salario_fixo_mensal = salario_fixo_mensal;

    return registro;
}

FolhaDePagamentoIndividual_t criar_folha_individual_terceirizado(char nome_do_funcionario[], float taxa_por_hora, float horas_trabalhadas, int qtd_de_contratos, float bonus_por_contrato) {
    FolhaDePagamentoIndividual_t registro;

    strcpy(registro.nome_do_funcionario, nome_do_funcionario);
    registro.qtd_de_contratos = qtd_de_contratos;
    registro.bonus_por_contrato = bonus_por_contrato;

    registro.func = calcular_folha_individual;

    // Dados especificos para funcionario terceirizado
    registro.tipo_de_vinculo = terceirizacao;
    registro.dados_do_vinculo.terceirizado.taxa_por_hora = taxa_por_hora;
    registro.dados_do_vinculo.terceirizado.horas_trabalhadas = horas_trabalhadas;

    return registro;
}

float calcular_folha_individual(FolhaDePagamentoIndividual_t* folha_individual) {
    float pagamento_base = 0, bonus = 0;

    if (folha_individual->tipo_de_vinculo == clt) {
        pagamento_base = folha_individual->dados_do_vinculo.celetista.salario_fixo_mensal;
    } else if (folha_individual->tipo_de_vinculo == terceirizacao) {
        pagamento_base = folha_individual->dados_do_vinculo.terceirizado.taxa_por_hora * folha_individual->dados_do_vinculo.terceirizado.horas_trabalhadas;
    }

    bonus = folha_individual->qtd_de_contratos * folha_individual->bonus_por_contrato;

    return pagamento_base + bonus;
}


// --------------- Funcoes para manipulacao da lista encadeada ---------------

void insere_na_lista(Item_t *head, FolhaDePagamentoIndividual_t folha_individual) {
    // Criando ponteiro para novo item da lista e alocando memoria dinamicamente
    Item_t *novo = (Item_t *)malloc(sizeof(Item_t));

    // Inicializando o novo item
    novo->prox = NULL;
    novo->folha_individual = folha_individual;

    // Percorrendo toda a lista ate a ultima posicao
    Item_t *atual = head;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    // Adicionando o novo elemento na ultima posicao
    atual->prox = novo;
}

void imprimir_folhas(Item_t *head) {
    Item_t *atual = head->prox;

    // Percorrendo toda a lista ate a ultima posicao e imprimindo valores dos itens
    while (atual != NULL){
        printf("\xAF %s:\n", atual->folha_individual.nome_do_funcionario);

        printf("\tTipo de contratacao: ");
        if (atual->folha_individual.tipo_de_vinculo == clt) {
            printf("CLT\n");
        
            printf("\tSalario fixo mensal: R$ %.2f\n", atual->folha_individual.dados_do_vinculo.celetista.salario_fixo_mensal);
        } else if (atual->folha_individual.tipo_de_vinculo == terceirizacao) {
            printf("Terceirizacao\n");

            printf("\tValor por hora trabalhada: R$ %.2f\n", atual->folha_individual.dados_do_vinculo.terceirizado.taxa_por_hora);
            printf("\tHoras trabalhadas no mes: %.2f h\n", atual->folha_individual.dados_do_vinculo.terceirizado.horas_trabalhadas);
        } else {
            printf("\t[Erro] Tipo de contratacao invalida!\n");
        }

        printf("\tQuantidade de contratos assinados no mes: %i\n", atual->folha_individual.qtd_de_contratos);

        float pagamento = atual->folha_individual.func(&(atual->folha_individual));
        printf("\tPagamento de %s: R$ %.2f\n\n", atual->folha_individual.nome_do_funcionario, pagamento);

        atual = atual->prox;
    }
}

float calcular_folha_total(Item_t *head) {
    Item_t *atual = head->prox;
    float total = 0;

    // Percorrendo toda a lista ate a ultima posicao
    while (atual != NULL){
        total += atual->folha_individual.func(&(atual->folha_individual));
        atual = atual->prox;
    }

    return total;
}

void liberar_memoria(Item_t *head) {
    // Ponteiro para o inicio da lista
    Item_t *atual = head->prox;

    // Ponteiro para o item a ser liberado
    Item_t *liberado;

    // Percorrendo a lista liberando memoria utilizada por todos os itens
    while (atual != NULL) {
        liberado = atual;
        atual = atual->prox;
        free(liberado);
    }   
}
