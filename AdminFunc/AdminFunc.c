#include <stdio.h>
#include "AdminFunc.h"
#include "GerenciarUsuarios/GerenciarUsuarios.h"
#include "GerenciarVans/GerenciarVans.h"

void AdminFunc()
{
    int escolha;

    printf("Olá Admin\n");

    do
    {
        printf("\n===== AREA DO ADMINISTRADOR =====\n");
        printf("1 - Gerenciar usuarios\n");
        printf("2 - Gerenciar vans\n");
        printf("3 - Listar usuarios\n");
        printf("4 - Listar vans\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            GerenciarUsuarios();
            break;
        
        case 2:
            GerenciarVans();
            break;
            
        case 3:
            printf("Lista de usuarios\n");
            break;

        case 4:
            printf("Lista de vans\n");
            break;

        case 0:
            printf("Saindo da area do administrador...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } 
    while (escolha != 0);
}