
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuario.h"

#define ARQUIVO_USUARIOS "dados/usuarios.csv"
#define ARQUIVO_VANS "dados/vans.csv"
#define ARQUIVO_TEMP "dados/usuarios_temp.csv"

// Limpa o restante da linha do teclado
void LimparEntrada(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Verifica se uma van existe no arquivo CSV
int VanExiste(int id)
{
    FILE *arquivo = fopen(ARQUIVO_VANS, "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    int idArquivo;
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "%d,", &idArquivo) == 1 &&
            idArquivo == id)
        {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Cadastrar usuario
void AdicionarUsuario(User *usuario)
{
    if (usuario == NULL)
    {
        printf("Erro: usuario invalido!\n");
        return;
    }

    printf("\n===== CADASTRAR USUARIO =====\n");

    printf("ID: ");
    if (scanf("%d", &usuario->id) != 1)
    {
        printf("ID invalido!\n");
        LimparEntrada();
        return;
    }

    printf("Nome: ");
    scanf(" %99[^\n]", usuario->nome);

    printf("Email: ");
    scanf(" %99[^\n]", usuario->email);

    printf("Senha: ");
    scanf(" %49[^\n]", usuario->senha);

    printf("Telefone: ");
    scanf(" %19[^\n]", usuario->telefone);

    printf("Nome do aluno: ");
    scanf(" %99[^\n]", usuario->nomeAluno);

    printf("ID da van: ");

    if (scanf("%d", &usuario->vanId) != 1)
    {
        printf("ID da van invalido!\n");
        LimparEntrada();
        return;
    }

    // Verifica se a van está cadastrada
    if (!VanExiste(usuario->vanId))
    {
        printf("Erro: essa van nao esta cadastrada!\n");
        return;
    }

    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios!\n");
        return;
    }

    fprintf(arquivo, "%d,%s,%s,%s,%s,%s,%d\n",
            usuario->id,
            usuario->nome,
            usuario->email,
            usuario->senha,
            usuario->telefone,
            usuario->nomeAluno,
            usuario->vanId);

    fclose(arquivo);

    printf("Usuario salvo com sucesso!\n");
}

// Excluir usuario
void ExcluirUsuario(void)
{
    int id;
    int idArquivo;
    int encontrado = 0;
    char linha[512];

    printf("\n===== EXCLUIR USUARIO =====\n");
    printf("Digite o ID do usuario que deseja excluir: ");

    if (scanf("%d", &id) != 1)
    {
        printf("ID invalido!\n");
        LimparEntrada();
        return;
    }

    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios!\n");
        return;
    }

    FILE *temporario = fopen(ARQUIVO_TEMP, "w");

    if (temporario == NULL)
    {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "%d,", &idArquivo) == 1 &&
            idArquivo == id)
        {
            encontrado = 1;
        }
        else
        {
            fputs(linha, temporario);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrado)
    {
        remove(ARQUIVO_TEMP);
        printf("Usuario com ID %d nao encontrado!\n", id);
        return;
    }

    if (rename(ARQUIVO_TEMP, ARQUIVO_USUARIOS) != 0)
    {
        perror("Erro ao atualizar o arquivo de usuarios");
        remove(ARQUIVO_TEMP);
        return;
    }

    printf("Usuario excluido com sucesso!\n");
}

// Editar usuario
void EditarUsuario(void)
{
    int id;
    int idArquivo;
    int encontrado = 0;
    char linha[512];

    User usuario;

    printf("\n===== EDITAR USUARIO =====\n");
    printf("Digite o ID do usuario que deseja editar: ");

    if (scanf("%d", &id) != 1)
    {
        printf("ID invalido!\n");
        LimparEntrada();
        return;
    }

    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios!\n");
        return;
    }

    FILE *temporario = fopen(ARQUIVO_TEMP, "w");

    if (temporario == NULL)
    {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "%d,", &idArquivo) == 1 &&
            idArquivo == id)
        {
            int campos = sscanf(
                linha,
                "%d,%99[^,],%99[^,],%49[^,],%19[^,],%99[^,],%d",
                &usuario.id,
                usuario.nome,
                usuario.email,
                usuario.senha,
                usuario.telefone,
                usuario.nomeAluno,
                &usuario.vanId
            );

            if (campos != 7)
            {
                printf("Erro: registro do usuario invalido!\n");

                fclose(arquivo);
                fclose(temporario);
                remove(ARQUIVO_TEMP);
                return;
            }

            encontrado = 1;

            printf("\nUsuario encontrado: %s\n", usuario.nome);
            printf("Digite os novos dados:\n");

            printf("Nome: ");
            scanf(" %99[^\n]", usuario.nome);

            printf("Email: ");
            scanf(" %99[^\n]", usuario.email);

            printf("Senha: ");
            scanf(" %49[^\n]", usuario.senha);

            printf("Telefone: ");
            scanf(" %19[^\n]", usuario.telefone);

            printf("Nome do aluno: ");
            scanf(" %99[^\n]", usuario.nomeAluno);

            printf("ID da van: ");

            if (scanf("%d", &usuario.vanId) != 1)
            {
                printf("ID da van invalido!\n");
                LimparEntrada();

                fclose(arquivo);
                fclose(temporario);
                remove(ARQUIVO_TEMP);
                return;
            }

            // Verifica se a nova van existe
            if (!VanExiste(usuario.vanId))
            {
                printf("Erro: essa van nao esta cadastrada!\n");

                fclose(arquivo);
                fclose(temporario);
                remove(ARQUIVO_TEMP);
                return;
            }

            fprintf(
                temporario,
                "%d,%s,%s,%s,%s,%s,%d\n",
                usuario.id,
                usuario.nome,
                usuario.email,
                usuario.senha,
                usuario.telefone,
                usuario.nomeAluno,
                usuario.vanId
            );
        }
        else
        {
            fputs(linha, temporario);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    if (!encontrado)
    {
        remove(ARQUIVO_TEMP);
        printf("Usuario com ID %d nao encontrado!\n", id);
        return;
    }

    if (rename(ARQUIVO_TEMP, ARQUIVO_USUARIOS) != 0)
    {
        perror("Erro ao atualizar o arquivo de usuarios");
        remove(ARQUIVO_TEMP);
        return;
    }

    printf("Usuario atualizado com sucesso!\n");
}
