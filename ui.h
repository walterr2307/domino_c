#ifndef UI_H
#define UI_H

extern int ind_mesa_esq, ind_mesa_dir;
extern char str_mesa_esq[136], str_mesa_dir[136];

void iniciar_mesa(void);

void escrever_na_mesa(int lado1, int lado2);

void imprimir_tabuleiro(void);

char escolher_opcao_jogada(int jogada, int compra, int pulo);

void comecar_jogada(void);

#endif
