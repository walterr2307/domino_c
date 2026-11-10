#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

struct jogador
{
    int indice;
    int qtd_pecas;
    int lados_esq[21];
    int lados_dir[21];
    char nome[15];
};

int maior_dupla = -1, maior_soma = -1, maior_lado = -1;
int lado_esq, lado_dir, lados_esq[28], lados_dir[28];
int qtd_jogs, qtd_pecas_compra, qtd_pulos = 0;
int ind_mesa_esq = 5, ind_mesa_dir = 5;
int ind_jog, ind_peca, ind_compra;
int mesa, mesa_esq, mesa_dir;

char lado_mesa, str_mesa_esq[136] = "", str_mesa_dir[136] = "";
struct jogador jog, jogs[4];

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

void iniciar_mesa()
{
    sprintf(&str_mesa_esq[0], "[%d|%d]", lado_esq, lado_dir);
    sprintf(&str_mesa_dir[0], "[%d|%d]", lado_dir, lado_esq);

    remover_peca();
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

    remover_peca();
}

void imprimir_tabuleiro()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("Lado Esquerdo:\n%s\n\n", str_mesa_esq);
    printf("Lado Direito:\n%s\n", str_mesa_dir);

    printf("\nPecas de %s:\n", jog.nome);

    for (int i = 0; i < jog.qtd_pecas; i++)
        printf("%d.[%d|%d] ",
               i + 1,
               jog.lados_esq[i],
               jog.lados_dir[i]);

    printf("\n\nPecas para compra: %d\n", qtd_pecas_compra);
}

char escolher_opcao_jogada(int jogada, int compra, int pulo)
{
    char opcao_turno;

    while (1)
    {
        printf("\nInsira 'j' para jogar uma peca");
        printf(", 'c' para comprar");
        printf(", 'p' para pular a vez");
        printf(" e 's' para salvar e sair: ");

        if (scanf(" %c", &opcao_turno) != 1)
        {
            printf("\n\tErro ao ler a entrada.\n");
            continue;
        }

        opcao_turno = tolower(opcao_turno);

        if (opcao_turno != 'j' && opcao_turno != 'c' &&
                opcao_turno != 'p' && opcao_turno != 's')
            printf("\n\tErro: opcao invalida.\n");

        else if (opcao_turno == 'j' && !jogada)
            printf("\n\tErro: jogadas indisponiveis.\n");
        else if (opcao_turno == 'c' && !compra)
            printf("\n\tErro: compra negada.\n");
        else if (opcao_turno == 'p' && !pulo)
            printf("\n\tErro: nao pode pular.\n");

        else
            break;
    }

    return opcao_turno;
}

int escolher_peca()
{
    int ind_peca;

    while (1)
    {
        printf("\n\nSelecione o indice correspondente a peca: ");

        if (scanf("%d", &ind_peca) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');
        }

        else if (ind_peca < 1 || ind_peca > jog.qtd_pecas)
            printf("\n\tErro: indice de peca invalido.\n");
        else
            break;
    }

    return --ind_peca;
}

char escolher_lado()
{
    char lado_mesa;

    while (1)
    {
        printf("\nEscolha 'e' para o lado esquerdo");
        printf(" e 'd' para o lado direito: ");

        if (scanf(" %c", &lado_mesa) != 1)
        {
            printf("\n\tErro ao ler a entrada.\n");
            continue;
        }

        lado_mesa = tolower(lado_mesa);

        if (lado_mesa != 'e' && lado_mesa != 'd')
            printf("\n\tErro: escolha invalida. Digite 'e' ou 'd'.\n");
        else
            break;
    }

    return lado_mesa;
}

void comecar_jogada()
{
    while(1)
    {
        ind_peca = escolher_peca();

        lado_esq = jog.lados_esq[ind_peca];
        lado_dir = jog.lados_dir[ind_peca];

        lado_mesa = escolher_lado();
        mesa = lado_mesa == 'e' ? mesa_esq : mesa_dir;

        if (lado_esq != mesa && lado_dir != mesa)
            printf("\n\tErro: a peca nao pode ser jogada nesse lado.\n");
        else
            break;
    }
}

int ler_qtd_jogs()
{
    int qtd_jogs;

    while (1)
    {
        printf("\nInsira a quantidade de jogadores (2 a 4): ");

        if (scanf("%d", &qtd_jogs) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");

            while (getchar() != '\n');
            continue;
        }

        if (qtd_jogs < 2 || qtd_jogs > 4)
            printf("\n\tErro: quantidade de jogadores invalida.\n");
        else
            break;
    }

    return qtd_jogs;
}

void embaralhar_pecas()
{
    int j, copia;

    srand(time(NULL));

    for (int i = 27; i > 0; i--)
    {
        j = rand() % (i + 1);

        copia = lados_esq[i];
        lados_esq[i] = lados_esq[j];
        lados_esq[j] = copia;

        copia = lados_dir[i];
        lados_dir[i] = lados_dir[j];
        lados_dir[j] = copia;
    }
}

void gerar_pecas()
{
    int i = 0;

    for (int j = 0; j <= 6; j++)
    {
        for (int k = 0; k <= j; k++)
        {
            lados_esq[i] = j;
            lados_dir[i++] = k;
        }
    }

    embaralhar_pecas();
}

void ajustar_jogadores()
{
    int k = 0;

    for (int i = 0; i < qtd_jogs; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            jogs[i].lados_esq[j] = lados_esq[k];
            jogs[i].lados_dir[j] = lados_dir[k++];
        }

        jogs[i].qtd_pecas = 7;
        jogs[i].indice = i;

        getchar();

        printf("Insira o nome do %d* jogador: ", i + 1);
        scanf("%14[^\n]", jogs[i].nome);
    }
}

void definir_maior_dupla(struct jogador jog)
{
    for (int i = 0; i < 7; i++)
    {
        int lado = jog.lados_esq[i];

        if (lado == jog.lados_dir[i] && lado > maior_dupla)
        {
            maior_dupla = lado;

            ind_jog = jog.indice;
            ind_peca = i;
        }

        if (maior_dupla == 6)
            break;
    }
}

void definir_maior_peca(struct jogador jog)
{
    for (int i = 0; i < 7; i++)
    {
        int lado = jog.lados_esq[i];
        int soma = lado + jog.lados_dir[i];

        if (soma > maior_soma || soma == maior_soma && lado > maior_lado)
        {
            maior_soma = soma;
            maior_lado = lado;

            ind_jog = jog.indice;
            ind_peca = i;
        }
    }
}

void definir_indices_iniciais()
{
    for (int i = 0; i < qtd_jogs; i++)
    {
        definir_maior_dupla(jogs[i]);

        if (maior_dupla == 6)
            break;
        if (maior_dupla < 0)
            definir_maior_peca(jogs[i]);
    }
}

void inicializar_jogo()
{
    qtd_jogs = ler_qtd_jogs();

    gerar_pecas();
    ajustar_jogadores();
    definir_indices_iniciais();

    jog = jogs[ind_jog];

    qtd_pecas_compra = 28 - 7 * qtd_jogs;
    ind_compra = 7 * qtd_jogs;

    lado_esq = jog.lados_esq[ind_peca];
    lado_dir = jog.lados_dir[ind_peca];

    mesa_esq = lado_dir;
    mesa_dir = lado_esq;

    iniciar_mesa();

    jogs[ind_jog] = jog;
}

void calcular_pts(int pontos[])
{
    for (int i = 0; i < qtd_jogs; i++)
    {
        struct jogador jog = jogs[i];

        for (int j = 0; j < jog.qtd_pecas; j++)
            pontos[i] += jog.lados_esq[j] + jog.lados_dir[j];
    }
}

int calcular_menor_qtd_pts(int pontos[], int *ptr_ind)
{
    int menor_qtd_pts = 999;

    for (int i = 0; i < qtd_jogs; i++)
    {
        if (pontos[i] < menor_qtd_pts)
        {
            menor_qtd_pts = pontos[i];
            *ptr_ind = i;
        }
    }

    return menor_qtd_pts;
}

int empatou(int pontos[], int menor_qtd_pts)
{
    int qtd_atingiram = 0;

    for (int i = 0; i < qtd_jogs; i++)
    {
        if (pontos[i] == menor_qtd_pts)
            ++qtd_atingiram;
        if (qtd_atingiram > 1)
            return 1;
    }

    return 0;
}

int retornar_ind_menor_peca()
{
    int indice = 0, menor_lado = 99, menor_soma = 99;

    for (int i = 0; i < qtd_jogs; i++)
    {
        struct jogador jog = jogs[i];

        for (int j = 0; j < jog.qtd_pecas; j++)
        {
            int lado = jog.lados_esq[j];
            int soma = lado + jog.lados_dir[j];

            if (soma < menor_soma || soma == menor_soma && lado < menor_lado)
            {
                menor_lado = lado;
                menor_soma = soma;

                indice = i;
            }

            if (menor_soma == 0)
                return indice;
        }
    }

    return indice;
}

struct jogador retornar_vencedor()
{
    int ind_vencedor, menor_qtd_pts, pontos[] = {0, 0, 0, 0};

    calcular_pts(pontos);
    menor_qtd_pts = calcular_menor_qtd_pts(pontos, &ind_vencedor);

    if (empatou(pontos, menor_qtd_pts))
        ind_vencedor = retornar_ind_menor_peca();

    return jogs[ind_vencedor];
}

void imprimir_vencedor()
{
    if (qtd_jogs == qtd_pulos)
        jog = retornar_vencedor();

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("\n\t%s venceu!!!\n", jog.nome);
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
        ind_jog = compra ? ind_jog : ++ind_jog % qtd_jogs;
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
