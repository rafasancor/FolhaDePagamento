#include <stdio.h>

// Prototipação das funções
float calcularValeTransporte(float salarioBruto);
float calcularPlanoSaude(int dependentes, char tipoPlano);
float calcularFGTS(float salarioBruto, float gratificacao);
float calcularINSS(float salarioBruto, float gratificacao);
float calcularSalarioFamilia(float salarioBruto, int dependentesMenores14);
float calcularIR(float salarioBruto, float gratificacao, float inss, int dependentes);
float calcularSalarioLiquido(float salarioBruto, float gratificacao, int dependentesMenores14, int dependentesPlano, char tipoPlano, char utilizaVT);

void menu();

// Função principal
int main() {
    menu();
    return 0;
}

// Implementação das funções
void menu() {
    int opcao;
    float salarioBruto, gratificacao;
    int dependentesMenores14, dependentesPlano;
    char tipoPlano, utilizaVT;

    // Entrada de dados básicos
    printf("Informe o salario bruto: ");
    scanf("%f", &salarioBruto);
    printf("Informe o valor da gratificacao: ");
    scanf("%f", &gratificacao);
    printf("Informe o numero de dependentes menores de 14 anos: ");
    scanf("%d", &dependentesMenores14);
    printf("Informe o numero total de dependentes no plano de saude: ");
    scanf("%d", &dependentesPlano);
    printf("Informe o tipo de plano de saude (E para enfermaria ou Q para quarto): ");
    scanf(" %c", &tipoPlano);
    printf("Utiliza vale transporte? (S para sim ou N para nao): ");
    scanf(" %c", &utilizaVT);

    do {
        printf("\nMENU DE OPCOES\n");
        printf("1. Calcular Vale Transporte\n");
        printf("2. Calcular Plano de Saude\n");
        printf("3. Calcular FGTS\n");
        printf("4. Calcular INSS\n");
        printf("5. Calcular Salario Familia\n");
        printf("6. Calcular IR\n");
        printf("7. Calcular Salario Liquido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Desconto do Vale Transporte: R$ %.2f\n", calcularValeTransporte(salarioBruto));
                break;
            case 2:
                printf("Desconto do Plano de Saude: R$ %.2f\n", calcularPlanoSaude(dependentesPlano, tipoPlano));
                break;
            case 3:
                printf("Valor do FGTS: R$ %.2f\n", calcularFGTS(salarioBruto, gratificacao));
                break;
            case 4:
                printf("Desconto do INSS: R$ %.2f\n", calcularINSS(salarioBruto, gratificacao));
                break;
            case 5:
                printf("Valor do Salario Familia: R$ %.2f\n", calcularSalarioFamilia(salarioBruto, dependentesMenores14));
                break;
            case 6:
                printf("Desconto do IR: R$ %.2f\n", calcularIR(salarioBruto, gratificacao, calcularINSS(salarioBruto, gratificacao), dependentesMenores14));
                break;
            case 7:
                printf("Salario Liquido: R$ %.2f\n", calcularSalarioLiquido(salarioBruto, gratificacao, dependentesMenores14, dependentesPlano, tipoPlano, utilizaVT));
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// Cálculo do Vale Transporte
float calcularValeTransporte(float salarioBruto) {
    float descontoMaximo = salarioBruto * 0.06;
    float custoTransporte = 44 * 6.0;
    return (custoTransporte < descontoMaximo) ? custoTransporte : descontoMaximo;
}

// Cálculo do Plano de Saúde
float calcularPlanoSaude(int dependentes, char tipoPlano) {
    float custoPorDependente = (tipoPlano == 'E' || tipoPlano == 'e') ? 89.90 : 119.90;
    return dependentes * custoPorDependente;
}

// Cálculo do FGTS
float calcularFGTS(float salarioBruto, float gratificacao) {
    return (salarioBruto + gratificacao) * 0.08;
}

// Cálculo do INSS
float calcularINSS(float salarioBruto, float gratificacao) {
    float salario = salarioBruto + gratificacao;
    if (salario <= 1100.00) return salario * 0.075;
    if (salario <= 2203.48) return salario * 0.09;
    if (salario <= 3305.22) return salario * 0.12;
    if (salario <= 6433.57) return salario * 0.14;
    return 6433.57 * 0.14; // Teto máximo
}

// Cálculo do Salário Família
float calcularSalarioFamilia(float salarioBruto, int dependentesMenores14) {
    if (salarioBruto <= 1503.25) return dependentesMenores14 * 51.27;
    return 0.0;
}

// Cálculo do IR
float calcularIR(float salarioBruto, float gratificacao, float inss, int dependentes) {
    float deducaoPorDependente = dependentes * 189.59;
    float baseCalculo = (salarioBruto + gratificacao) - inss - deducaoPorDependente;

    if (baseCalculo <= 1903.98) return 0.0;
    if (baseCalculo <= 2826.65) return baseCalculo * 0.075 - 142.80;
    if (baseCalculo <= 3751.05) return baseCalculo * 0.15 - 354.80;
    if (baseCalculo <= 4664.68) return baseCalculo * 0.225 - 636.13;
    return baseCalculo * 0.275 - 869.36;
}

// Cálculo do Salário Líquido
float calcularSalarioLiquido(float salarioBruto, float gratificacao, int dependentesMenores14, int dependentesPlano, char tipoPlano, char utilizaVT) {
    float vt = (utilizaVT == 'S' || utilizaVT == 's') ? calcularValeTransporte(salarioBruto) : 0.0;
    float planoSaude = calcularPlanoSaude(dependentesPlano, tipoPlano);
    float inss = calcularINSS(salarioBruto, gratificacao);
    float salarioFamilia = calcularSalarioFamilia(salarioBruto, dependentesMenores14);
    float ir = calcularIR(salarioBruto, gratificacao, inss, dependentesMenores14);

    return (salarioBruto + gratificacao) - vt - planoSaude - inss + salarioFamilia - ir;
}
