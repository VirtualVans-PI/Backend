#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Van.h"

#define ARQUIVO_VANS "dados/vans.csv"

typedef struct {
    int id;
    char placa[10];
    char modelo[50];
    int capacidade;
    char motorista[100];
} Van;

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

    printf("Placa: ");
    scanf(" %9[^\n]", van.placa);

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

            printf("Nova placa: ");
            scanf(" %9[^\n]", van.placa);

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
            continue;
        }

        fputs(linha, temporario);
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrou) {
        remove("dados/vans_temp.csv");
        printf("Nenhuma van encontrada com esse ID.\n");
        return;
    }

    if (rename("dados/vans_temp.csv", ARQUIVO_VANS) != 0) {
        printf("Erro ao atualizar o arquivo de vans!\n");
        return;
    }

    printf("Van excluida com sucesso!\n");
}
