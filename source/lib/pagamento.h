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

typedef struct FolhaDePagamentoIndividual {
    char nome_do_funcionario[50];
    enum vinculo_empregaticio tipo_de_vinculo;
    union dados_empregaticios dados_do_vinculo;
    int qtd_de_contratos;
    float bonus_por_contrato;
    float (*func)(struct FolhaDePagamentoIndividual*);
} FolhaDePagamentoIndividual_t;

typedef struct Item {
    FolhaDePagamentoIndividual_t folha_individual;
    struct Item *prox;
} Item_t;


// --------------- Funcoes ---------------

FolhaDePagamentoIndividual_t criar_folha_individual_clt(char nome_do_funcionario[], float salario_fixo_mensal, int qtd_de_contratos, float bonus_por_contrato);
FolhaDePagamentoIndividual_t criar_folha_individual_terceirizado(char nome_do_funcionario[], float taxa_por_hora, float horas_trabalhadas, int qtd_de_contratos, float bonus_por_contrato);
float calcular_folha_individual(FolhaDePagamentoIndividual_t* folha_individual);
void insere_na_lista(Item_t *head, FolhaDePagamentoIndividual_t folha_individual);
void imprimir_folhas(Item_t *head);
float calcular_folha_total(Item_t *head);
void liberar_memoria(Item_t *head);

#endif