#include "jogador.h"
#include "main.h"
#include "ui.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int maior_dupla = -1, maior_soma = -1, maior_lado = -1;

int ler_qtd_jogs()
{
    int qtd_jogs;

    while (1)
    {
        printf("\nInsira a quantidade de jogadores (2 a 4): ");

        if (scanf("%d", &qtd_jogs) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");

            while (getchar() != '\n');
            continue;
        }

        if (qtd_jogs < 2 || qtd_jogs > 4)
            printf("\n\tErro: quantidade de jogadores invalida.\n");
        else
            break;
    }

    return qtd_jogs;
}

embaralhar_pecas()
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

void gerar_pecas()
{
    int i = 0;

    for (int j = 0; j <= 6; j++)
    {
        for (int k = 0; k <= j; k++)
        {
            lados_esq[i] = j;
            lados_dir[i++] = k;
        }
    }

    embaralhar_pecas();
}

void ajustar_jogadores()
{
    int k = 0;

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

void definir_indices_iniciais()
{
    for (int i = 0; i < qtd_jogs; i++)
    {
        definir_maior_dupla(jogs[i]);

        if (maior_dupla == 6)
            break;
        if (maior_dupla < 0)
            definir_maior_peca(jogs[i]);
    }
}

void inicializar_jogo()
{
    qtd_jogs = ler_qtd_jogs();

    gerar_pecas();
    ajustar_jogadores();
    definir_indices_iniciais();

    jog = jogs[ind_jog];

    qtd_pecas_compra = 28 - 7 * qtd_jogs;
    ind_compra = 7 * qtd_jogs;

    lado_esq = jog.lados_esq[ind_peca];
    lado_dir = jog.lados_dir[ind_peca];

    mesa_esq = lado_dir;
    mesa_dir = lado_esq;

    iniciar_mesa();

    jogs[ind_jog] = jog;
}
