#ifndef MAIN_H
#define MAIN_H

#include "jogador.h"

extern int lado_esq, lado_dir, lados_esq[28], lados_dir[28];
extern int qtd_jogs, qtd_pecas_compra, qtd_pulos;
extern int ind_jog, ind_peca, ind_compra;
extern int mesa, mesa_esq, mesa_dir;

extern struct jogador jog, jogs[4];
extern char lado_mesa;

void remover_peca(void);

#endif
