#include "fim_de_jogo.h"
#include <stdio.h>

void calcular_pts(struct jogador jogs[], int pontos[], int qtd_jogs)
{
    for (int i = 0; i < qtd_jogs; i++)
    {
        struct jogador jog = jogs[i];

        for (int j = 0; j < jog.qtd_pecas; j++)
            pontos[i] += jog.lados_esq[j] + jog.lados_dir[j];
    }
}

int calcular_menor_qtd_pts(int pontos[], int qtd_jogs, int *ptr_ind)
{
    int menor_qtd_pts = 999;

    for (int i = 0; i < qtd_jogs; i++)
    {
        if (pontos[i] < menor_qtd_pts)
        {
            menor_qtd_pts = pontos[i];
            *ptr_ind = i;
        }
    }

    return menor_qtd_pts;
}

int empatou(int pontos[], int qtd_jogs, int menor_qtd_pts)
{
    int qtd_atingiram = 0;

    for (int i = 0; i < qtd_jogs; i++)
    {
        if (pontos[i] == menor_qtd_pts)
            ++qtd_atingiram;
        if (qtd_atingiram > 1)
            return 1;
    }

    return 0;
}

int retornar_ind_menor_peca(struct jogador jogs[], int qtd_jogs)
{
    int indice = 0, menor_lado = 99, menor_soma = 99;

    for (int i = 0; i < qtd_jogs; i++)
    {
        struct jogador jog = jogs[i];

        for (int j = 0; j < jog.qtd_pecas; j++)
        {
            int lado = jog.lados_esq[j];
            int soma = lado + jog.lados_dir[j];

            if (soma < menor_soma || soma == menor_soma && lado < menor_lado)
            {
                menor_lado = lado;
                menor_soma = soma;

                indice = i;
            }

            if (menor_soma == 0)
                return indice;
        }
    }

    return indice;
}

struct jogador retornar_vencedor(struct jogador jogs[], int qtd_jogs)
{
    int ind_vencedor, menor_qtd_pts, pontos[] = {0, 0, 0, 0};

    calcular_pts(jogs, pontos, qtd_jogs);
    menor_qtd_pts = calcular_menor_qtd_pts(pontos, qtd_jogs, &ind_vencedor);

    if (empatou(pontos, qtd_jogs, menor_qtd_pts))
        ind_vencedor = retornar_ind_menor_peca(jogs, qtd_jogs);

    return jogs[ind_vencedor];
}

void imprimir_vencedor(
    struct jogador jogs[],
    struct jogador jog,
    int qtd_jogs,
    int qtd_pulos
)
{
    if (qtd_jogs == qtd_pulos)
        jog = retornar_vencedor(jogs, qtd_jogs);

    printf("\n\t%s venceu!!!\n", jog.nome);
}
