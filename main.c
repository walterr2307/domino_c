#include "conf_iniciais.h"
#include "fim_de_jogo.h"
#include "jogador.h"
#include "menu.h"
#include "main.h"
#include "ui.h"

int lado_esq, lado_dir, lados_esq[28], lados_dir[28];
int qtd_jogs, qtd_pecas_compra, qtd_pulos = 0;
int ind_jog, ind_peca, ind_compra;
int mesa, mesa_esq, mesa_dir;

struct jogador jog, jogs[4];
char lado_mesa;

void remover_peca()
{
    int limite = jog.qtd_pecas - 1;

    for (int i = ind_peca; i < limite; i++)
    {
        jog.lados_esq[i] = jog.lados_esq[i + 1];
        jog.lados_dir[i] = jog.lados_dir[i + 1];
    }

    --jog.qtd_pecas;
}

void comprar_peca()
{
    int i = jog.qtd_pecas, j = ind_compra;

    jog.lados_esq[i] = lados_esq[j];
    jog.lados_dir[i] = lados_dir[j];

    ++jog.qtd_pecas;
    ++ind_compra;

    --qtd_pecas_compra;
}

void colocar_na_mesa()
{
    if (mesa == lado_esq)
    {
        escrever_na_mesa(lado_esq, lado_dir);
        mesa = lado_dir;
    }
    else
    {
        escrever_na_mesa(lado_dir, lado_esq);
        mesa = lado_esq;
    }

    if (lado_mesa == 'e')
        mesa_esq = mesa;
    else
        mesa_dir = mesa;
}

int verificar_pulos(char opcao_turno)
{
    switch (opcao_turno)
    {
    case 's':
        salvar_arquivo();

    case 'p':
        return ++qtd_pulos;

    case 'c':
        comprar_peca();
        break;

    case 'j':
        comecar_jogada();
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
        carregar_arquivo();
    else
        inicializar_jogo();
}

int main()
{
    int jogada = 0, compra = 0, pulo = 0;
    char opcao_turno;

    ajustar_conf_iniciais();

    do
    {
        ind_jog = compra ? ind_jog : (ind_jog + 1) % qtd_jogs;
        jog = jogs[ind_jog];

        imprimir_tabuleiro();

        jogada = pode_jogar();
        compra = !jogada && qtd_pecas_compra;
        pulo = !jogada && !compra;

        opcao_turno = escolher_opcao_jogada(jogada, compra, pulo);
        qtd_pulos = verificar_pulos(opcao_turno);

        jogs[ind_jog] = jog;
    }
    while (jog.qtd_pecas && qtd_pulos < qtd_jogs);

    imprimir_vencedor();
    limpar_arquivo();
}
