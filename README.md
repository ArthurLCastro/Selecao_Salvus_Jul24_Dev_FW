# Processo seletivo da **Salvus** - *Julho de 2024*
## *Teste Técnico - Desenvolvedor(a) de Sistemas Embarcados*

## Conteúdos:

- [Descrição](#descrição)
- [Questão proposta](#questão-proposta)
    - [Objetivo](#objetivo)
    - [Observação](#observação)
    - [Informações adicionais](#informações-adicionais)
- [Resolução](#resolução)
- [Pré-requisitos](#pré-requisitos)
    - [Para Linux](#para-linux)
    - [Para Windows](#para-windows)

## Descrição:

Este repositório contém os arquivos referentes a solução do teste técnico da 2ª etapa do processo seletivo da [Salvus](https://www.salvus.me/).

## Questão proposta:

A empresa SmartWork trabalha com múltiplos tipos de profissionais diferentes. No momento, eles podem aderir a um e apenas um dos seguintes tipos de contrato:

1. Funcionários CLT, que recebem um salário fixo mensal
2. Profissionais terceirizados, os quais recebem um valor fixo pago por hora trabalhada no mês.

Com o intuito de motivar seus colaboradores, a empresa decidiu criar uma política de remuneração por comissão, pagando um bônus fixo por contrato assinado, podendo esta ser adotada tanto por funcionários CLT quanto terceirizados.

**Exemplos:**

    João:
    Contrato: Terceirizado
    Valor por hora: R$ 50,00
    Horas trabalhadas: 100
    Total a receber: R$ 5000,00

    Marcela:
    Contrato: CLT
    Salário: R$ 3000,00
    Contratos assinados: 10
    Comissão por contrato: R$ 200,00
    Total a receber: R$ 5000,00

    Joaquim:
    Contrato: Terceirizado
    Valor por hora: R$ 30,00
    Horas trabalhadas: 180
    Contratos assinados: 12
    Comissão por contrato: R$ 200,00
    Total a receber: R$ 7800,00

**Custo total da folha de pagamento da empresa:** R$ 17800,00

### Objetivo:

Sua missão é desenvolver um conjunto de rotinas em C que permitam:

1. Cadastrar as informações do mês de um número arbitrário de funcionários
2. Calcular individualmente o total à pagar para cada funcionário
3. Calcular o total da folha de pagamento da empresa.

### Observação:

Não é necessário desenvolver uma interface com o usuário. As informações dos funcionários e as chamadas para as rotinas de cálculo podem ser chamadas diretamente na main. O objetivo deste exercício é criar as rotinas necessárias para gerar as informações, e não a forma como serão consumidas.

### Informações adicionais:

Deseja-se uma implementação enxuta das informações dos funcionários. Por exemplo, se um funcionário não é pago por hora, não há necessidade de armazenar as informações de hora trabalhada e taxa por hora. Quanto menos informações
redundantes ou não utilizadas, melhor.
De atenção à manutenção do código, evite código e dados duplicados e redundantes na implementação.

## Resolução:

O código fonte com a resolução da [Questão Proposta](#questão-proposta) encontra-se em [`/source`](/source/), tendo como arquivo principal [`main.c`](/source/main.c).

A estratégia de resolução utilizada consistiu na implementação de uma estrutura de dados chamada `FolhaDePagamentoIndividual`, que armazena as informações mensais de um funcionário em conjunto com uma outra estrutura, nomeada como `Item`, que equivale a um nó de uma lista encadeada. Foi desenvolvido um grupo de funções relacionadas a folha de pagamento (para criação e cálculos, por exemplo), além de funções dedicadas à manipulações da lista, como para alocar e liberar memória dinamicamente e de impressão dos dados dos pagamentos.

## Pré-requisitos:

Ter um compilador para linguagem C instalado na máquina. Por exemplo:

### Para Linux:
    
- [gcc](https://gcc.gnu.org/) (costuma vir instalado na maioria das distribuições GNU/Linux)

### Para Windows:

- [MinGW](https://sourceforge.net/projects/mingw/)

> *Observação:* </br> Certifique-se de que o compilador está configurado como variável de ambiente no seu SO.

> *Extensões sugeridas para *VScode:** </br> [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) </br> [C/C++ Compile Run](https://marketplace.visualstudio.com/items?itemName=danielpinto8zz6.c-cpp-compile-run)
