#include <stdio.h>
#include "GerenciarVans.h"
#include "Van.h"

void GerenciarVans(void)
{
    int escolha;

    do
    {
        printf("\n===== GERENCIAR VANS =====\n");
        printf("1 - Cadastrar van\n");
        printf("2 - Listar vans\n");
        printf("3 - Editar van\n");
        printf("4 - Excluir van\n");
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
                AdicionarVan();
                break;
            case 2:
                ListarVans();
                break;
            case 3:
                EditarVan();
                break;
            case 4:
                ExcluirVan();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (escolha != 0);
}