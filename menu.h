#ifndef MENU_H
#define MENU_H

#include "jogador.h"

int carregar_jogo(void);

void limpar_arquivo(void);

void salvar_arquivo(
    int mesa_esq,
    int mesa_dir,
    int lados_esq[],
    int lados_dir[],
    int ind_jog,
    int ind_compra,
    int ind_mesa_esq,
    int ind_mesa_dir,
    int qtd_jogs,
    int qtd_pecas_compra,
    char str_mesa_esq[],
    char str_mesa_dir[],
    struct jogador jogs[]
);

void carregar_arquivo(
    int *ptr_mesa_esq,
    int *ptr_mesa_dir,
    int lados_esq[],
    int lados_dir[],
    int *ptr_ind_jog,
    int *ptr_ind_compra,
    int *ptr_ind_mesa_esq,
    int *ptr_ind_mesa_dir,
    int *ptr_qtd_jogs,
    int *ptr_qtd_pecas_compra,
    char str_mesa_esq[],
    char str_mesa_dir[],
    struct jogador jogs[]
);

#endif
