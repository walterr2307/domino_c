#include "ui.h"
#include <stdlib.h>
#include <stdio.h>

void imprimir_tabuleiro(
    struct jogador jog,
    char str_mesa_esq[],
    char str_mesa_dir[],
    int qtd_pecas_compra
)
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

int escolher_opcao_jogada(
    int jogada_disponivel,
    int compra_liberada,
    int pulo_permitido
)
{
    int opcao_jogada;

    while (1)
    {
        printf("\nInsira 1 para jogar uma peca");
        printf(", 2 para comprar");
        printf(", 3 para pular a vez");
        printf(" e 0 salvar e sair: ");

        if (scanf("%d", &opcao_jogada) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');

            continue;
        }

        if (opcao_jogada < 0 || opcao_jogada > 3)
            printf("\n\tErro: opcao invalida.\n");
        else if (opcao_jogada == 1 && !jogada_disponivel)
            printf("\n\tErro: jogadas indisponiveis.\n");
        else if (opcao_jogada == 2 && !compra_liberada)
            printf("\n\tErro: compra negada.\n");
        else if (opcao_jogada == 3 && !pulo_permitido)
            printf("\n\tErro: nao pode pular.\n");
        else
            break;
    }

    return opcao_jogada;
}

int escolher_peca(struct jogador jog)
{
    int ind_peca = 0;

    while (ind_peca < 1 || ind_peca > jog.qtd_pecas)
    {
        printf("\n\nSelecione o indice correspondente a peca: ");

        if (scanf("%d", &ind_peca) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');

            continue;
        }

        if (ind_peca < 1 || ind_peca > jog.qtd_pecas)
            printf("\n\tErro: indice de peca invalido.\n");
    }

    return --ind_peca;
}

char escolher_lado()
{
    char lado_mesa = '\0';

    while (lado_mesa != 'e' && lado_mesa != 'd')
    {
        printf("\nEscolha 'e' para o lado esquerdo");
        printf(" e 'd' para o lado direito: ");

        if (scanf(" %c", &lado_mesa) != 1)
        {
            printf("\n\tErro ao ler a entrada.\n");
            continue;
        }

        if (lado_mesa == 'E' || lado_mesa == 'D')
            lado_mesa += 32;

        if (lado_mesa != 'e' && lado_mesa != 'd')
            printf("\n\tErro: escolha invalida. Digite 'e' ou 'd'.\n");
    }

    return lado_mesa;
}

void comecar_jogada(
    struct jogador jog,
    int *p_ind_peca,
    int *p_lado_esq,
    int *p_lado_dir,
    char *p_lado_mesa,
    int **p_ptr_mesa,
    int *p_mesa_esq,
    int *p_mesa_dir
)
{
    do
    {
        *p_ind_peca = escolher_peca(jog);

        *p_lado_esq = jog.lados_esq[*p_ind_peca];
        *p_lado_dir = jog.lados_dir[*p_ind_peca];

        *p_lado_mesa = escolher_lado();
        *p_ptr_mesa = *p_lado_mesa == 'e' ? p_mesa_esq : p_mesa_dir;

        if (*p_lado_esq != **p_ptr_mesa && *p_lado_dir != **p_ptr_mesa)
            printf("\n\tErro: a peca nao pode ser jogada nesse lado.\n");

    }
    while (*p_lado_esq != **p_ptr_mesa && *p_lado_dir != **p_ptr_mesa);
}
