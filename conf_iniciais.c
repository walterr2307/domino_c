#include "conf_iniciais.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int qtd_jogs = 0, *lados_esq, *lados_dir, ind_jog, ind_peca;
static int maior_dupla = -1, maior_soma = -1, maior_lado = -1;
static struct jogador *jogs;

int ler_qtd_jogs()
{
    while (qtd_jogs < 2 || qtd_jogs > 4)
    {
        printf("Digite a quantidade de jogadores, entre 2 e 4: ");

        if (scanf("%d", &qtd_jogs) != 1)
        {
            printf("\nErro: digite um numero inteiro.\n\n");
            while (getchar() != '\n');

            continue;
        }

        if (qtd_jogs < 2 || qtd_jogs > 4)
            printf("\nErro: a quantidade deve estar entre 2 e 4.\n\n");
    }

    printf("\n");

    return qtd_jogs;
}

void embaralhar_pecas()
{
    int j, copia;

    srand(time(NULL));

    for (int i = 27; i > 0; i--)
    {
        j = rand() % (i + 1);

        copia = lados_esq[i];
        lados_esq[i] = lados_esq[j];
        lados_esq[j] = copia;

        copia = lados_dir[i];
        lados_dir[i] = lados_dir[j];
        lados_dir[j] = copia;
    }
}

void gerar_pecas(int lados_esquerdos[], int lados_direitos[])
{
    int k = 0;

    lados_esq = lados_esquerdos;
    lados_dir = lados_direitos;

    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            lados_esq[k] = i;
            lados_dir[k++] = j;
        }
    }

    embaralhar_pecas();
}

void ajustar_jogadores(struct jogador jogadores[])
{
    int k = 0;

    jogs = jogadores;

    for (int i = 0; i < qtd_jogs; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            jogs[i].lados_esq[j] = lados_esq[k];
            jogs[i].lados_dir[j] = lados_dir[k++];
        }

        jogs[i].qtd_pecas = 7;
        jogs[i].indice = i;

        getchar();

        printf("Insira o nome do %d* jogador: ", i + 1);
        scanf("%14[^\n]", jogs[i].nome);
    }
}

void definir_maior_dupla(struct jogador jog)
{
    for (int i = 0; i < 7; i++)
    {
        int lado = jog.lados_esq[i];

        if (lado == jog.lados_dir[i] && lado > maior_dupla)
        {
            maior_dupla = lado;

            ind_jog = jog.indice;
            ind_peca = i;
        }

        if (maior_dupla == 6)
            break;
    }
}

void definir_maior_peca(struct jogador jog)
{
    for (int i = 0; i < 7; i++)
    {
        int lado = jog.lados_esq[i];
        int soma = lado + jog.lados_dir[i];

        if (soma > maior_soma || soma == maior_soma && lado > maior_lado)
        {
            maior_soma = soma;
            maior_lado = lado;

            ind_jog = jog.indice;
            ind_peca = i;
        }
    }
}

void definir_ind_iniciais(int *ptr_ind_jog, int *ptr_ind_peca)
{
    for (int i = 0; i < qtd_jogs; i++)
    {
        definir_maior_dupla(jogs[i]);

        if (maior_dupla == 6)
            break;
        if (maior_dupla == -1)
            definir_maior_peca(jogs[i]);
    }

    *ptr_ind_jog = ind_jog;
    *ptr_ind_peca = ind_peca;
}
