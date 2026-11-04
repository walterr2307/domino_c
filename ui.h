#ifndef UI_H
#define UI_H

#include "jogador.h"

void imprimir_tabuleiro(
    struct jogador jog,
    char str_mesa_esq[],
    char str_mesa_dir[],
    int qtd_pecas_compra
);

int escolher_opcao_jogada(
    int jogada_disponivel,
    int compra_liberada,
    int pulo_permitido
);

void comecar_jogada(
    struct jogador jog,
    int *p_ind_peca,
    int *p_lado_esq,
    int *p_lado_dir,
    char *p_lado_mesa,
    int **p_ptr_mesa,
    int *p_mesa_esq,
    int *p_mesa_dir
);

#endif
