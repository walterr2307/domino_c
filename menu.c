#include "jogador.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpar_arquivo()
{
    FILE *arq = fopen("save.txt", "w");

    if (arq == NULL)
    {
        printf("\n\tErro ao abrir arquivo.\n");
        exit(-1);
    }

    fclose(arq);
}

int arquivo_vazio()
{
    int arq_vazio = 0;
    FILE *arq = fopen("save.txt", "r");

    if (arq == NULL)
    {
        printf("\n\tErro ao abrir arquivo.\n");
        exit(-1);
    }

    if (fgetc(arq) == EOF)
    {
        printf("\n\tNao foi encontrado um salvamento.\n");
        arq_vazio = 1;
    }

    fclose(arq);
    return arq_vazio;
}

int carregar_jogo()
{
    int carregar = -1;

    while (carregar < 0 || carregar > 1)
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("0. Novo jogo\n");
        printf("1. Carregar jogo\n");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &carregar) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');

            continue;
        }

        if (carregar)
        {
            if (arquivo_vazio())
            {
                carregar = -1;
                continue;
            }
        }

        if (carregar < 0 || carregar > 1)
            printf("\n\tErro: opcao invalida.\n");
    }

    if (!carregar)
        limpar_arquivo();

    return carregar;
}

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
)
{
    FILE *arq = fopen("save.txt", "w");

    if (arq == NULL)
    {
        printf("Erro ao criar arquivo.\n");
        exit(-1);
    }

    fprintf(arq, "%d %d\n", mesa_esq, mesa_dir);

    fprintf(arq, "%d %d %d %d %d %d\n",
            ind_jog,
            ind_compra,
            ind_mesa_esq,
            ind_mesa_dir,
            qtd_jogs,
            qtd_pecas_compra);

    fprintf(arq, "%s\n", str_mesa_esq);
    fprintf(arq, "%s\n", str_mesa_dir);

    for (int i = 0; i < 28; i++)
        fprintf(arq, "%d %d\n", lados_esq[i], lados_dir[i]);

    for (int i = 0; i < qtd_jogs; i++)
    {
        fprintf(arq, "%d\n", jogs[i].qtd_pecas);
        fprintf(arq, "%s\n", jogs[i].nome);

        for (int j = 0; j < jogs[i].qtd_pecas; j++)
            fprintf(arq, "%d %d\n", jogs[i].lados_esq[j], jogs[i].lados_dir[j]);
    }

    fclose(arq);
    exit(0);
}

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
)
{
    FILE *arq = fopen("save.txt", "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir save.txt\n");
        exit(-1);;
    }

    fscanf(arq, "%d %d", ptr_mesa_esq, ptr_mesa_dir);

    fscanf(arq, "%d %d %d %d %d %d",
           ptr_ind_jog,
           ptr_ind_compra,
           ptr_ind_mesa_esq,
           ptr_ind_mesa_dir,
           ptr_qtd_jogs,
           ptr_qtd_pecas_compra);

    fgetc(arq);

    fgets(str_mesa_esq, 141, arq);
    fgets(str_mesa_dir, 141, arq);

    str_mesa_esq[strcspn(str_mesa_esq, "\n")] = '\0';
    str_mesa_dir[strcspn(str_mesa_dir, "\n")] = '\0';

    for (int i = 0; i < 28; i++)
    {
        fscanf(arq, "%d %d",
               &lados_esq[i],
               &lados_dir[i]);
    }

    for (int i = 0; i < *ptr_qtd_jogs; i++)
    {
        fscanf(arq, "%d", &jogs[i].qtd_pecas);
        fgetc(arq);
        fgets(jogs[i].nome, sizeof(jogs[i].nome), arq);

        jogs[i].nome[strcspn(jogs[i].nome, "\n")] = '\0';

        for (int j = 0; j < jogs[i].qtd_pecas; j++)
            fscanf(arq, "%d %d", &jogs[i].lados_esq[j], &jogs[i].lados_dir[j]);
    }

    fclose(arq);
}
