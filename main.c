#include "conf_iniciais.h"
#include "fim_de_jogo.h"
#include "jogador.h"
#include "menu.h"
#include "ui.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int lado_esq, lado_dir, mesa_esq, mesa_dir, lados_esq[28], lados_dir[28];
int ind_jog, ind_peca, ind_compra, ind_mesa_esq = 0, ind_mesa_dir = 0;
int qtd_jogs, qtd_pecas_compra, *ptr_mesa;
char lado_mesa, str_mesa_esq[141] = "", str_mesa_dir[141] = "";
struct jogador jog, jogs[4];

void remover_peca()
{
    int i = ind_jog, limite = jog.qtd_pecas - 1;

    for (int j = ind_peca; j < limite; j++)
    {
        jogs[i].lados_esq[j] = jog.lados_esq[j + 1];
        jogs[i].lados_dir[j] = jog.lados_dir[j + 1];
    }

    --jogs[i].qtd_pecas;
    --jog.qtd_pecas;
}

void comprar_peca()
{
    int i = ind_jog, j = jog.qtd_pecas, k = ind_compra;

    jogs[i].lados_esq[j] = lados_esq[k];
    jogs[i].lados_dir[j] = lados_dir[k];

    ++jogs[i].qtd_pecas;
    ++ind_compra;

    --qtd_pecas_compra;
    --ind_jog;
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
}

void colocar_na_mesa()
{
    int lado1, lado2;

    if (*ptr_mesa == lado_esq)
    {
        *ptr_mesa = lado_dir;

        lado1 = lado_esq;
        lado2 = lado_dir;
    }
    else
    {
        *ptr_mesa = lado_esq;

        lado1 = lado_dir;
        lado2 = lado_esq;
    }

    escrever_na_mesa(lado1, lado2);
    remover_peca();
}

void iniciar_mesa()
{
    lado_esq = jog.lados_esq[ind_peca];
    lado_dir = jog.lados_dir[ind_peca];

    ptr_mesa = &mesa_esq;
    mesa_esq = lado_dir;
    lado_mesa = 'e';

    escrever_na_mesa(lado_esq, lado_dir);

    ptr_mesa = &mesa_dir;
    mesa_dir = lado_esq;
    lado_mesa = 'd';

    escrever_na_mesa(lado_dir, lado_esq);
}

int verificar_pulos(int opcao_jogada, int qtd_pulos)
{
    switch (opcao_jogada)
    {
    case 0:
        salvar_arquivo(mesa_esq, mesa_dir, lados_esq, lados_dir, --ind_jog,
                       ind_compra, ind_mesa_esq, ind_mesa_dir, qtd_jogs,
                       qtd_pecas_compra, str_mesa_esq, str_mesa_dir, jogs);

    case 3:
        return ++qtd_pulos;

    case 2:
        comprar_peca();
        break;

    case 1:
        comecar_jogada(jog, &ind_peca, &lado_esq, &lado_dir, &lado_mesa,
                       &ptr_mesa, &mesa_esq, &mesa_dir);

        colocar_na_mesa();
    }

    return 0;
}

int pode_jogar()
{
    for (int i = 0; i < jog.qtd_pecas; i++)
    {
        int lado_esq = jog.lados_esq[i];
        int lado_dir = jog.lados_dir[i];

        if (lado_esq == mesa_esq || lado_esq == mesa_dir ||
                lado_dir == mesa_esq || lado_dir == mesa_dir)
            return 1;
    }

    return 0;
}

void ajustar_conf_iniciais()
{
    if (carregar_jogo())
    {
        carregar_arquivo(&mesa_esq, &mesa_dir, lados_esq, lados_dir, &ind_jog,
                         &ind_compra, &ind_mesa_esq, &ind_mesa_dir, &qtd_jogs,
                         &qtd_pecas_compra, str_mesa_esq, str_mesa_dir, jogs);

        jog = jogs[0];
    }
    else
    {
        qtd_jogs = ler_qtd_jogs();

        gerar_pecas(lados_esq, lados_dir);
        ajustar_jogadores(jogs);
        definir_ind_iniciais(&ind_jog, &ind_peca);

        jog = jogs[ind_jog];

        ind_compra = 7 * qtd_jogs;
        qtd_pecas_compra = 28 - ind_compra;

        iniciar_mesa();
        remover_peca();
    }
}

int main()
{
    int qtd_pulos = 0, opcao_jogada, jogada, compra, pulo;

    ajustar_conf_iniciais();

    while (jog.qtd_pecas && qtd_pulos < qtd_jogs)
    {
        ind_jog = (ind_jog + 1) % qtd_jogs;
        jog = jogs[ind_jog];

        imprimir_tabuleiro(jog, str_mesa_esq, str_mesa_dir, qtd_pecas_compra);

        jogada = pode_jogar();
        compra = !jogada && qtd_pecas_compra;
        pulo = !jogada && !compra;

        opcao_jogada = escolher_opcao_jogada(jogada, compra, pulo);
        qtd_pulos = verificar_pulos(opcao_jogada, qtd_pulos);
    }

    imprimir_vencedor(jogs, jog, qtd_jogs, qtd_pulos);
    limpar_arquivo();
}
