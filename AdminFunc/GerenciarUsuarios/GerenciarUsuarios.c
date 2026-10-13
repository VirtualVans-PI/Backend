#include <stdio.h>
#include "GerenciarUsuarios.h"
#include "Usuario.h"

void GerenciarUsuarios()
{
    int escolha;
    do
    {
        printf("\n===== GERENCIAMENTO DE USUÁRIOS =====\n");
        printf("1 - Adicionar usuários\n");
        printf("2 - Excluir usuários\n");
        printf("3 - Editar usuários\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
        {
            User novoUsuario;
            AdicionarUsuario(&novoUsuario);
            break;
        }
        
        case 2:
            ExcluirUsuario();
            break;
            
        case 3:
            EditarUsuario();
            break;

        case 0:
            printf("Saindo do gerenciamento de usuários...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } 
    while (escolha != 0);
}