#ifndef CONF_INICIAIS_H
#define CONF_INICIAIS_H

#include "jogador.h"

int ler_qtd_jogs(void);

void gerar_pecas(int lados_esquerdos[], int lados_direitos[]);

void ajustar_jogadores(struct jogador jogadores[]);

void definir_ind_iniciais(int *ptr_ind_jog, int *ptr_ind_peca);

#endif
