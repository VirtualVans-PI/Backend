#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Van.h"

#define ARQUIVO_USUARIOS "dados/usuarios.csv"
#define ARQUIVO_VANS "dados/vans.csv"

int VanTemUsuarios(int idVan)
{
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    char linha[512];
    int vanIdArquivo;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha,
            "%*d,%*99[^,],%*99[^,],%*49[^,],%*19[^,],%*99[^,],%d",
            &vanIdArquivo) == 1)
        {
            if (vanIdArquivo == idVan)
            {
                fclose(arquivo);
                return 1;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

int ValidarPlaca(char placa[])
{
    // Formato antigo: ABC-1234
    if (strlen(placa) == 8)
    {
        return (
            placa[0] >= 'A' && placa[0] <= 'Z' &&
            placa[1] >= 'A' && placa[1] <= 'Z' &&
            placa[2] >= 'A' && placa[2] <= 'Z' &&
            placa[3] == '-' &&
            placa[4] >= '0' && placa[4] <= '9' &&
            placa[5] >= '0' && placa[5] <= '9' &&
            placa[6] >= '0' && placa[6] <= '9' &&
            placa[7] >= '0' && placa[7] <= '9'
        );
    }

    // Formato Mercosul: ABC1D23
    if (strlen(placa) == 7)
    {
        return (
            placa[0] >= 'A' && placa[0] <= 'Z' &&
            placa[1] >= 'A' && placa[1] <= 'Z' &&
            placa[2] >= 'A' && placa[2] <= 'Z' &&
            placa[3] >= '0' && placa[3] <= '9' &&
            placa[4] >= 'A' && placa[4] <= 'Z' &&
            placa[5] >= '0' && placa[5] <= '9' &&
            placa[6] >= '0' && placa[6] <= '9'
        );
    }

    return 0;
}

void AdicionarVan(void)
{
    Van van;

    printf("\n===== CADASTRAR VAN =====\n");

    printf("ID: ");
    if (scanf("%d", &van.id) != 1) {
        printf("ID invalido!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Placa (ABC-1234 ou ABC1D23): ");
    scanf(" %9[^\n]", van.placa);

    for (int i = 0; van.placa[i] != '\0'; i++)
    {
        if (van.placa[i] >= 'a' && van.placa[i] <= 'z')
        {
            van.placa[i] -= 32;
        }
    }

    if (!ValidarPlaca(van.placa))
    {
        printf("Placa invalida! Use ABC-1234 ou ABC1D23.\n");
        return;
    }

    printf("Modelo: ");
    scanf(" %49[^\n]", van.modelo);

    printf("Capacidade de passageiros: ");
    if (scanf("%d", &van.capacidade) != 1 ||
        van.capacidade <= 0) {
        printf("Capacidade invalida!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Nome do motorista: ");
    scanf(" %99[^\n]", van.motorista);

    FILE *arquivo = fopen(ARQUIVO_VANS, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vans!\n");
        return;
    }

    fprintf(arquivo, "%d,%s,%s,%d,%s\n",
            van.id,
            van.placa,
            van.modelo,
            van.capacidade,
            van.motorista);

    fclose(arquivo);

    printf("Van cadastrada com sucesso!\n");
}

void ListarVans(void)
{
    Van van;
    FILE *arquivo = fopen(ARQUIVO_VANS, "r");

    if (arquivo == NULL) {
        printf("Nenhuma van cadastrada ou arquivo inexistente.\n");
        return;
    }

    char linha[256];
    int encontrou = 0;

    printf("\n===== VANS CADASTRADAS =====\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%d,%9[^,],%49[^,],%d,%99[^\n]",
                   &van.id,
                   van.placa,
                   van.modelo,
                   &van.capacidade,
                   van.motorista) == 5) {

            printf("\nID: %d\n", van.id);
            printf("Placa: %s\n", van.placa);
            printf("Modelo: %s\n", van.modelo);
            printf("Capacidade: %d passageiros\n", van.capacidade);
            printf("Motorista: %s\n", van.motorista);

            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma van cadastrada.\n");
    }

    fclose(arquivo);
}

void EditarVan(void)
{
    int idBusca;
    int idArquivo;
    int encontrou = 0;
    char linha[256];
    int edicaoValida = 1;

    Van van;

    printf("\n===== EDITAR VAN =====\n");
    printf("Digite o ID da van que deseja editar: ");

    if (scanf("%d", &idBusca) != 1) {
        printf("ID invalido!\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        return;
    }

    FILE *arquivo = fopen(ARQUIVO_VANS, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vans!\n");
        return;
    }

    FILE *temporario = fopen("dados/vans_temp.csv", "w");

    if (temporario == NULL) {
        fclose(arquivo);
        printf("Erro ao criar arquivo temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        if (sscanf(linha, "%d,", &idArquivo) == 1 &&
            idArquivo == idBusca) {

            encontrou = 1;

            if (sscanf(linha, "%d,%9[^,],%49[^,],%d,%99[^\n]",
                       &van.id,
                       van.placa,
                       van.modelo,
                       &van.capacidade,
                       van.motorista) != 5) {

                printf("Erro ao ler os dados da van!\n");
                fputs(linha, temporario);
                continue;
            }

            printf("\nVan encontrada!\n");
            printf("Placa atual: %s\n", van.placa);
            printf("Modelo atual: %s\n", van.modelo);
            printf("Capacidade atual: %d\n", van.capacidade);
            printf("Motorista atual: %s\n", van.motorista);

            printf("\nDigite os novos dados:\n");

            printf("Nova placa (ABC-1234 ou ABC1D23): ");
            scanf(" %9[^\n]", van.placa);

            for (int i = 0; van.placa[i] != '\0'; i++)
            {
                if (van.placa[i] >= 'a' && van.placa[i] <= 'z')
                {
                    van.placa[i] -= 32;
                }
            }

            if (!ValidarPlaca(van.placa))
            {
                printf("Placa invalida! Edicao cancelada.\n");

                fputs(linha, temporario);
                edicaoValida = 0;
                continue;
            }

            printf("Novo modelo: ");
            scanf(" %49[^\n]", van.modelo);

            printf("Nova capacidade: ");

           if (scanf("%d", &van.capacidade) != 1 || van.capacidade <= 0) 
           {
            printf("Capacidade invalida! Edicao cancelada.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            edicaoValida = 0;
            fputs(linha, temporario);
            continue;
           }

            printf("Novo motorista: ");
            scanf(" %99[^\n]", van.motorista);

            fprintf(temporario, "%d,%s,%s,%d,%s\n",
                    van.id,
                    van.placa,
                    van.modelo,
                    van.capacidade,
                    van.motorista);

        } else {
            fputs(linha, temporario);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) 
    {
        remove("dados/vans_temp.csv");
        printf("Nenhuma van encontrada com esse ID.\n");
        return;
    }

    if (!edicaoValida) {
        remove("dados/vans_temp.csv");
        printf("Nenhuma alteracao foi salva.\n");
        return;
    }

    if (rename("dados/vans_temp.csv", ARQUIVO_VANS) != 0) 
    {
        printf("Erro ao atualizar o arquivo de vans!\n");
        return;
    }

    printf("Van editada com sucesso!\n");
}

void ExcluirVan(void)
{
    int idBusca;
    int idArquivo;
    int encontrou = 0;
    char linha[256];

    printf("\n===== EXCLUIR VAN =====\n");
    printf("Digite o ID da van que deseja excluir: ");

    if (scanf("%d", &idBusca) != 1)
    {
        printf("ID invalido!\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        return;
    }

    // Verifica se existem usuarios vinculados a van
    if (VanTemUsuarios(idBusca))
    {
        printf("Erro: nao e possivel excluir esta van!\n");
        printf("Existem usuarios vinculados a ela.\n");
        return;
    }

    FILE *arquivo = fopen(ARQUIVO_VANS, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de vans!\n");
        return;
    }

    FILE *temporario = fopen("dados/vans_temp.csv", "w");

    if (temporario == NULL)
    {
        fclose(arquivo);
        printf("Erro ao criar arquivo temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "%d,", &idArquivo) == 1 &&
            idArquivo == idBusca)
        {
            encontrou = 1;
            continue;
        }

        fputs(linha, temporario);
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou)
    {
        remove("dados/vans_temp.csv");
        printf("Nenhuma van encontrada com esse ID.\n");
        return;
    }

    if (rename("dados/vans_temp.csv", ARQUIVO_VANS) != 0)
    {
        printf("Erro ao atualizar o arquivo de vans!\n");
        return;
    }

    printf("Van excluida com sucesso!\n");
}

void BuscarVanPorPlaca(void)
{
    FILE *arquivo = fopen(ARQUIVO_VANS, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo de vans!\n");
        return;
    }

    Van van;
    char linha[256];
    char placaBusca[10];
    int encontrou = 0;

    printf("Digite a placa da van: ");
    scanf(" %9[^\n]", placaBusca);

    // Converte a placa digitada para maiusculas
    for (int i = 0; placaBusca[i] != '\0'; i++)
    {
        if (placaBusca[i] >= 'a' && placaBusca[i] <= 'z')
        {
            placaBusca[i] -= 32;
        }
    }

    if (!ValidarPlaca(placaBusca))
    {
        printf("Formato de placa invalido!\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "%d,%9[^,],%49[^,],%d,%99[^\n]",
                   &van.id,
                   van.placa,
                   van.modelo,
                   &van.capacidade,
                   van.motorista) == 5)
        {
            if (strcmp(van.placa, placaBusca) == 0)
            {
                printf("\n===== VAN ENCONTRADA =====\n");
                printf("ID: %d\n", van.id);
                printf("Placa: %s\n", van.placa);
                printf("Modelo: %s\n", van.modelo);
                printf("Capacidade: %d passageiros\n", van.capacidade);
                printf("Motorista: %s\n", van.motorista);

                encontrou = 1;
                break;
            }
        }
    }

    if (!encontrou)
    {
        printf("Nenhuma van encontrada com essa placa.\n");
    }

    fclose(arquivo);
}

void BuscarVanPorID(void)
{
    FILE *arquivo = fopen(ARQUIVO_VANS, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo de vans!\n");
        return;
    }

    Van van;
    char linha[256];
    int idBusca;
    int encontrou = 0;

    printf("Digite o ID da van: ");

    if (scanf("%d", &idBusca) != 1)
    {
        printf("ID invalido!\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "%d,%9[^,],%49[^,],%d,%99[^\n]",
                   &van.id,
                   van.placa,
                   van.modelo,
                   &van.capacidade,
                   van.motorista) == 5)
        {
            if (van.id == idBusca)
            {
                printf("\n===== VAN ENCONTRADA =====\n");
                printf("ID: %d\n", van.id);
                printf("Placa: %s\n", van.placa);
                printf("Modelo: %s\n", van.modelo);
                printf("Capacidade: %d passageiros\n", van.capacidade);
                printf("Motorista: %s\n", van.motorista);

                encontrou = 1;
                break;
            }
        }
    }

    if (!encontrou)
        printf("Nenhuma van encontrada com esse ID.\n");

    fclose(arquivo);
}

void ConsultarVans(void)
{
    int escolha;

    do
    {
        printf("\n===== CONSULTAR VANS =====\n");
        printf("1 - Listar todas as vans\n");
        printf("2 - Buscar por ID\n");
        printf("3 - Buscar por placa\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");

        if (scanf("%d", &escolha) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            escolha = -1;
        }

        switch (escolha)
        {
            case 1:
                ListarVans();
                break;

            case 2:
                BuscarVanPorID();
                break;

            case 3:
                BuscarVanPorPlaca();
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (escolha != 0);
}