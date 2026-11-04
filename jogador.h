#ifndef JOGADOR_H
#define JOGADOR_H

struct jogador
{
    int indice;
    int qtd_pecas;
    int lados_esq[21];
    int lados_dir[21];
    char nome[15];
};

#endif
