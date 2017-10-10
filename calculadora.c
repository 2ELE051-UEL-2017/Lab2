#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M_PI 3.1415926535897932384626

double soma(double x, double y);
double subtracao(double x, double y);
double multiplicacao(double x, double y);
double divisao(double x, double y);
double fatorial(double n);
double potencia(double x, int y);
double exponencial(double x);
double seno(double x);
int MDC(int x, int y);

#define TESTE1(FUNCAO,X,ESPERADO,STRING,FORMATO)                 \
if ((res = FUNCAO(X)) != ESPERADO)                               \
{                                                                \
    printf("Erro: " STRING " = " FORMATO "\n", X,  res);         \
    return 0;                                                    \
}

#define TESTE1APROX(FUNCAO,X,ESPERADO,INTERVALO,STRING,FORMATO)  \
res = FUNCAO(X);                                                 \
if (fabs(ESPERADO) < INTERVALO)                                  \
{                                                                \
    if (fabs(res - ESPERADO) > INTERVALO)                        \
    {                                                            \
        printf("Erro: " STRING " = " FORMATO "\n", X, res);      \
        return 0;                                                \
    }                                                            \
}                                                                \
else if (fabs(1.0 - res/ESPERADO) > INTERVALO)                   \
{                                                                \
    printf("Erro: " STRING " = " FORMATO "\n", X, res);          \
    return 0;                                                    \
}

#define TESTE2(FUNCAO,X,Y,ESPERADO,STRING,FORMATO)               \
if ((res = FUNCAO(X,Y)) != ESPERADO)                             \
{                                                                \
    printf("Erro: " STRING " = " FORMATO "\n", X, Y, res);       \
    return 0;                                                    \
}


#define TESTESOMA(X,Y,Z) TESTE2(soma, X, Y, Z, "(%lf) + (%lf)", "%lf")
#define TESTESUBTRACAO(X,Y,Z) TESTE2(subtracao, X, Y, Z, "(%lf) - (%lf)", "%lf")
#define TESTEMULTIPLICACAO(X,Y,Z) TESTE2(multiplicacao, X, Y, Z, "(%lf) * (%lf)", "%lf")
#define TESTEDIVISAO(X,Y,Z) TESTE2(divisao, X, Y, Z, "(%lf) / (%lf)", "%lf")
#define TESTEFATORIAL(X,Y) TESTE1(fatorial, X, Y, "%lf!", "%lf")
#define TESTEPOTENCIA(X,Y,Z) TESTE2(potencia, X, Y, Z, "(%lf) elevado a (%d)", "%lf")
#define TESTEEXPONENCIAL(X,Y) TESTE1APROX(exponencial, X, Y, 0.000001, "exponencial(%lf)", "%lf")
#define TESTESENO(X, Y) TESTE1APROX(seno, X, Y, 0.000001, "seno(%lf)", "%le");
#define TESTEMDC(X,Y,Z) TESTE2(MDC, X, Y, Z, "MDC(%d,%d)", "%d")

int rodarTesteSoma()
{
    double res;

    TESTESOMA(1.0, 1.0, 2.0);
    TESTESOMA(1.0, -1.0, 0.0);
    TESTESOMA(5.0, 2.5, 7.5);
    TESTESOMA(-10.0, 5.0, -5.0);

    return 1;
}

int rodarTesteSubtracao()
{
    double res;

    TESTESUBTRACAO(2.0, 1.0, 1.0);
    TESTESUBTRACAO(5.0, 5.0, 0.0);
    TESTESUBTRACAO(1.0, -1.0, 2.0);
    TESTESUBTRACAO(-3.0, 4.0, -7.0);
    TESTESUBTRACAO(-5.0, -7.5, 2.5);

    return 1;
}

int rodarTesteMultiplicacao()
{
    double res;

    TESTEMULTIPLICACAO(1.0, 1.0, 1.0);
    TESTEMULTIPLICACAO(2.0, 0.0, 0.0);
    TESTEMULTIPLICACAO(2.0, -2.0, -4.0);
    TESTEMULTIPLICACAO(-1.5, -1.5, 2.25);

    return 1;
}

int rodarTesteDivisao()
{
    double res;

    TESTEDIVISAO(1.0, 1.0, 1.0);
    TESTEDIVISAO(6.0, 3.0, 2.0);
    TESTEDIVISAO(5.0, 2.5, 2.0);
    TESTEDIVISAO(-5.0, -2.0, 2.5);
    TESTEDIVISAO(8.0, -2.0, -4.0);
    TESTEDIVISAO(-1.0, 4.0, -0.25);

    return 1;
}

int rodarTesteFatorial()
{
    double res;

    TESTEFATORIAL(0.0, 1.0);
    TESTEFATORIAL(1.0, 1.0);
    TESTEFATORIAL(5.0, 120.0);
    TESTEFATORIAL(7.0, 5040.0);

    return 1;
}

int rodarTestePotencia()
{
    double res;

    TESTEPOTENCIA(1.0, 1, 1.0);
    TESTEPOTENCIA(2.0, -1, 0.5);
    TESTEPOTENCIA(2.0, -3, 0.125);
    TESTEPOTENCIA(1.5, 2, 2.25);
    TESTEPOTENCIA(-3.0, 6, 729.0);
    TESTEPOTENCIA(-5.0, 3, -125.0);
    TESTEPOTENCIA(-2.0, -2, 0.25);
    TESTEPOTENCIA(-2.0, -3, -0.125);
    TESTEPOTENCIA(2.0, 30, 1073741824.0);

    return 1;
}

int rodarTesteExponencial()
{
    double res;

    TESTEEXPONENCIAL(0.0, 1.0);
    TESTEEXPONENCIAL(1.0, 2.718282);
    TESTEEXPONENCIAL(-1.0, 0.36787944);
    TESTEEXPONENCIAL(2.5, 12.182494);
    TESTEEXPONENCIAL(-5.0, 0.006737947);

    return 1;
}

int rodarTesteSeno()
{
    double res;

    TESTESENO(0.0, 0.0);
    TESTESENO(M_PI/2.0, 1.0);
    TESTESENO(M_PI, 0.0);
    TESTESENO(3.0*M_PI/2.0, -1.0);
    TESTESENO(2.0*M_PI, 0.0);
    TESTESENO(M_PI/4.0, 0.70710678);
    TESTESENO(M_PI/3.0, 0.866025403);

    return 1;
}

int rodarTesteMDC()
{
    int res;

    TESTEMDC(1, 1, 1);
    TESTEMDC(2, 1, 1);
    TESTEMDC(3, 2, 1);
    TESTEMDC(2, 3, 1);
    TESTEMDC(4, 2, 2);
    TESTEMDC(6, 9, 3);
    TESTEMDC(12, 15, 3);
    TESTEMDC(210333944, 184543593, 31337);

    return 1;
}

int rodarTeste(const char* nome, int (*funcao)())
{
    int res;
    printf("Testando %s... \n", nome);
    if ((res = funcao()) != 0)
        printf("Teste %s OK\n", nome);
    else
        printf("Erro no teste %s\n", nome);
    return res;
}

void lerDoisDoubles(double* x, double* y)
{
    printf("Digite o primeiro numero: ");
    scanf("%lf", x);
    printf("Digite o segundo numero: ");
    scanf("%lf", y);
}

void lerUmDouble(double* x)
{
    printf("Digite o numero: ");
    scanf("%lf", x);
}

void lerUmDoubleUmInt(double* x, int* y)
{
    printf("Digite o primeiro numero: ");
    scanf("%lf", x);
    printf("Digite o segundo numero: ");
    scanf("%d", y);
}

void lerDoisInts(int* x, int* y)
{
    printf("Digite o primeiro numero: ");
    scanf("%d", x);
    printf("Digite o segundo numero: ");
    scanf("%d", y);
}

void resultadoDouble(double x)
{
    printf("Resultado: %lf\n", x);
}

void resultadoInt(int x)
{
    printf("Resultado: %d\n", x);
}

typedef struct
{
    const char* nome;
    int (*funcao)();
} funcoes_t;

int main()
{
    int i, opcao;
    double x, y;
    int z, w;
    int* funcaoDisponivel;
    int numFuncoes, numFuncoesDisponiveis = 0;

    const char* opcoes[] = {
        "1 - Soma",
        "2 - Subtracao",
        "3 - Multiplicacao",
        "4 - Divisao",
        "5 - Fatorial",
        "6 - Potencia",
        "7 - Exponencial",
        "8 - Seno",
        "9 - MDC",
    };

    funcoes_t funcoes[] =
    {
        { "soma", rodarTesteSoma },
        { "subtracao", rodarTesteSubtracao },
        { "multiplicacao", rodarTesteMultiplicacao },
        { "divisao", rodarTesteDivisao },
        { "fatorial", rodarTesteFatorial },
        { "potencia", rodarTestePotencia },
        { "exponencial", rodarTesteExponencial },
        { "seno", rodarTesteSeno },
        { "MDC", rodarTesteMDC },
    };

    numFuncoes = sizeof(funcoes)/sizeof(funcoes_t);

    funcaoDisponivel = malloc(sizeof(int)*numFuncoes);
    memset(funcaoDisponivel, 0, sizeof(int)*numFuncoes);

    printf("***********************\n");
    printf("***** CALCULADORA *****\n");
    printf("***********************\n");
    printf("\n");
    printf("Testando funcoes disponiveis na calculadora...\n");
    printf("\n");

    for (i = 0; i < numFuncoes; i++)
        funcaoDisponivel[i] = rodarTeste(funcoes[i].nome, funcoes[i].funcao);

    printf("\n");
    printf("Opcoes disponiveis:\n");

    for (i = 0; i < numFuncoes; i++)
        if (funcaoDisponivel[i])
        {
            numFuncoesDisponiveis++;
            printf("%s\n", opcoes[i]);
        }

    if (numFuncoesDisponiveis == 0)
    {
        printf("Nenhuma funcao disponivel, saindo da calculadora\n");
        return -1;
    }

    printf("\n");
    // mdc
    // Resolver equacao de segundo grau -- 2 funcoes para 2 raizes possiveis
    // Soma de PG -- numerica e exata
    // 

    while (1)
    {
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        if (opcao > 0 && opcao <= numFuncoes && funcaoDisponivel[opcao-1])
            break;
        else
            printf("Opcao invalida, tente novamente\n");
    }

    switch (opcao)
    {
        case 1:
            lerDoisDoubles(&x, &y);
            resultadoDouble(soma(x,y));
            break;
        case 2:
            lerDoisDoubles(&x, &y);
            resultadoDouble(subtracao(x,y));
            break;
        case 3:
            lerDoisDoubles(&x, &y);
            resultadoDouble(multiplicacao(x,y));
            break;
        case 4:
            lerDoisDoubles(&x, &y);
            resultadoDouble(divisao(x,y));
            break;
        case 5:
            lerUmDouble(&x);
            resultadoDouble(fatorial(x));
            break;
        case 6:
            lerUmDoubleUmInt(&x, &z);
            resultadoDouble(potencia(x,z));
            break;
        case 7:
            lerUmDouble(&x);
            resultadoDouble(exponencial(x));
            break;
        case 8:
            lerUmDouble(&x);
            resultadoDouble(seno(x));
            break;
        case 9:
            lerDoisInts(&z, &w);
            resultadoInt(MDC(z,w));
            break;
    }


    return 0;
}
