#include "jogador.h"
#include "main.h"
#include "menu.h"
#include "ui.h"
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
    int arq_vazio = 1;
    FILE *arq = fopen("save.txt", "r");

    if (arq)
    {
        arq_vazio = fgetc(arq) == EOF;
        fclose(arq);
    }

    return arq_vazio;
}

int carregar_jogo()
{
    int carregar, arq_vazio = arquivo_vazio();

    while (1)
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("0. Novo jogo\n");
        printf("1. Carregar jogo\n");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &carregar) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');
        }

        else if (carregar == 1 && arq_vazio)
            printf("\n\tNao foi encontrado um salvamento.\n");
        else if (carregar < 0 || carregar > 1)
            printf("\n\tErro: opcao invalida.\n");
        else
            break;
    }

    if (!carregar)
        limpar_arquivo();

    return carregar;
}

void salvar_arquivo()
{
    FILE *arq = fopen("save.txt", "w");

    if (arq == NULL)
    {
        printf("Erro ao criar arquivo.\n");
        exit(-1);
    }

    fprintf(arq, "%d %d\n", mesa_esq, mesa_dir);

    fprintf(arq, "%d %d %d %d %d %d %d\n",
            --ind_jog,
            ind_compra,
            ind_mesa_esq,
            ind_mesa_dir,
            qtd_jogs,
            qtd_pecas_compra,
            qtd_pulos);

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

void carregar_arquivo()
{
    FILE *arq = fopen("save.txt", "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir save.txt\n");
        exit(-1);
    }

    fscanf(arq, "%d %d",
           &mesa_esq,
           &mesa_dir);

    fscanf(arq, "%d %d %d %d %d %d %d",
           &ind_jog,
           &ind_compra,
           &ind_mesa_esq,
           &ind_mesa_dir,
           &qtd_jogs,
           &qtd_pecas_compra,
           &qtd_pulos);

    fgetc(arq);

    fgets(str_mesa_esq, 136, arq);
    fgets(str_mesa_dir, 136, arq);

    str_mesa_esq[strcspn(str_mesa_esq, "\n")] = '\0';
    str_mesa_dir[strcspn(str_mesa_dir, "\n")] = '\0';

    for (int i = 0; i < 28; i++)
    {
        fscanf(arq, "%d %d",
               &lados_esq[i],
               &lados_dir[i]);
    }

    for (int i = 0; i < qtd_jogs; i++)
    {
        fscanf(arq, "%d", &jogs[i].qtd_pecas);

        fgetc(arq);

        fgets(jogs[i].nome,
              sizeof(jogs[i].nome),
              arq);

        jogs[i].nome[
            strcspn(jogs[i].nome, "\n")
        ] = '\0';

        for (int j = 0; j < jogs[i].qtd_pecas; j++)
        {
            fscanf(arq, "%d %d",
                   &jogs[i].lados_esq[j],
                   &jogs[i].lados_dir[j]);
        }
    }

    fclose(arq);
}
