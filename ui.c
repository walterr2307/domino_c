#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "main.h"
#include "ui.h"

int ind_mesa_esq = 5, ind_mesa_dir = 5;
char str_mesa_esq[136] = "", str_mesa_dir[136] = "";

void iniciar_mesa()
{
    sprintf(&str_mesa_esq[0], "[%d|%d]", lado_esq, lado_dir);
    sprintf(&str_mesa_dir[0], "[%d|%d]", lado_dir, lado_esq);

    remover_peca();
}

void escrever_na_mesa(int lado1, int lado2)
{
    if (lado_mesa == 'e')
    {
        sprintf(&str_mesa_esq[ind_mesa_esq], "[%d|%d]", lado1, lado2);
        ind_mesa_esq += 5;
    }
    else
    {
        sprintf(&str_mesa_dir[ind_mesa_dir], "[%d|%d]", lado1, lado2);
        ind_mesa_dir += 5;
    }

    remover_peca();
}

void imprimir_tabuleiro()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("Lado Esquerdo:\n%s\n\n", str_mesa_esq);
    printf("Lado Direito:\n%s\n", str_mesa_dir);

    printf("\nPecas de %s:\n", jog.nome);

    for (int i = 0; i < jog.qtd_pecas; i++)
        printf("%d.[%d|%d] ",
               i + 1,
               jog.lados_esq[i],
               jog.lados_dir[i]);

    printf("\n\nPecas para compra: %d\n", qtd_pecas_compra);
}

char escolher_opcao_jogada(int jogada, int compra, int pulo)
{
    char opcao_turno;

    while (1)
    {
        printf("\nInsira 'j' para jogar uma peca");
        printf(", 'c' para comprar");
        printf(", 'p' para pular a vez");
        printf(" e 's' para salvar e sair: ");

        if (scanf(" %c", &opcao_turno) != 1)
        {
            printf("\n\tErro ao ler a entrada.\n");
            continue;
        }

        opcao_turno = tolower(opcao_turno);

        if (opcao_turno != 'j' && opcao_turno != 'c' &&
                opcao_turno != 'p' && opcao_turno != 's')
            printf("\n\tErro: opcao invalida.\n");

        else if (opcao_turno == 'j' && !jogada)
            printf("\n\tErro: jogadas indisponiveis.\n");
        else if (opcao_turno == 'c' && !compra)
            printf("\n\tErro: compra negada.\n");
        else if (opcao_turno == 'p' && !pulo)
            printf("\n\tErro: nao pode pular.\n");

        else
            break;
    }

    return opcao_turno;
}

int escolher_peca()
{
    int ind_peca;

    while (1)
    {
        printf("\n\nSelecione o indice correspondente a peca: ");

        if (scanf("%d", &ind_peca) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');
        }

        else if (ind_peca < 1 || ind_peca > jog.qtd_pecas)
            printf("\n\tErro: indice de peca invalido.\n");
        else
            break;
    }

    return --ind_peca;
}

char escolher_lado()
{
    char lado_mesa;

    while (1)
    {
        printf("\nEscolha 'e' para o lado esquerdo");
        printf(" e 'd' para o lado direito: ");

        if (scanf(" %c", &lado_mesa) != 1)
        {
            printf("\n\tErro ao ler a entrada.\n");
            continue;
        }

        lado_mesa = tolower(lado_mesa);

        if (lado_mesa != 'e' && lado_mesa != 'd')
            printf("\n\tErro: escolha invalida. Digite 'e' ou 'd'.\n");
        else
            break;
    }

    return lado_mesa;
}

void comecar_jogada()
{
    while(1)
    {
        ind_peca = escolher_peca();

        lado_esq = jog.lados_esq[ind_peca];
        lado_dir = jog.lados_dir[ind_peca];

        lado_mesa = escolher_lado();
        mesa = lado_mesa == 'e' ? mesa_esq : mesa_dir;

        if (lado_esq != mesa && lado_dir != mesa)
            printf("\n\tErro: a peca nao pode ser jogada nesse lado.\n");
        else
            break;
    }
}
