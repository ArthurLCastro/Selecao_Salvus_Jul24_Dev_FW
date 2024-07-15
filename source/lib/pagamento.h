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

    struct FolhaDePagamentoIndividual *proximo_registro;       // Para lista encadeada

    float (*func)(struct FolhaDePagamentoIndividual*);
} FolhaDePagamentoIndividual_t;


// --------------- Funcoes para manipular a Lista Encadeada ---------------
void cadastrar_folha_clt(FolhaDePagamentoIndividual_t *ptr_primeiro_registro, char nome_do_funcionario[], float salario_fixo_mensal, int qtd_de_contratos, float bonus_por_contrato);
void cadastrar_folha_terceirizado(FolhaDePagamentoIndividual_t *ptr_primeiro_registro, char nome_do_funcionario[], float taxa_por_hora, float horas_trabalhadas, int qtd_de_contratos, float bonus_por_contrato);

float calcular_folha_individual(FolhaDePagamentoIndividual_t* ptr_primeiro_registro);
void visualizar_folhas(FolhaDePagamentoIndividual_t *ptr_primeiro_registro);
float calcular_folha_total(FolhaDePagamentoIndividual_t *ptr_primeiro_registro);

void liberar_memoria(FolhaDePagamentoIndividual_t* ptr_primeiro_registro);

#endif