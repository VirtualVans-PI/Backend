#include <stdio.h>
#include <string.h>
#include "Usuario.h"

void AdicionarUsuario(User *usuario)

{
    printf("\n===== CADASTRAR USUARIO =====\n");

    printf("ID: ");
    scanf("%d", &usuario->id);

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
    scanf("%d", &usuario->vanId);

    FILE *arquivo = fopen("dados/usuarios.csv", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo CSV!\n");
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

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        return;
    }

    FILE *arquivo = fopen("dados/usuarios.csv", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios!\n");
        return;
    }

    FILE *temporario = fopen("dados/usuarios_temp.csv", "w");

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
        remove("dados/usuarios_temp.csv");
        printf("Usuario com ID %d nao encontrado!\n", id);
        return;
    }

    if (rename("dados/usuarios_temp.csv",
               "dados/usuarios.csv") != 0)
    {
        perror("Erro ao atualizar o arquivo de usuarios");
        remove("dados/usuarios_temp.csv");
        return;
    }

    printf("Usuario excluido com sucesso!\n");
}


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

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        return;
    }

    FILE *arquivo = fopen("dados/usuarios.csv", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios!\n");
        return;
    }

    FILE *temporario = fopen("dados/usuarios_temp.csv", "w");

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
                remove("dados/usuarios_temp.csv");
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

                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                {
                }

                fclose(arquivo);
                fclose(temporario);
                remove("dados/usuarios_temp.csv");
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
        remove("dados/usuarios_temp.csv");
        printf("Usuario com ID %d nao encontrado!\n", id);
        return;
    }

    if (rename("dados/usuarios_temp.csv",
               "dados/usuarios.csv") != 0)
    {
        perror("Erro ao atualizar o arquivo de usuarios");
        remove("dados/usuarios_temp.csv");
        return;
    }

    printf("Usuario atualizado com sucesso!\n");
}