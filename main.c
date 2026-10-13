#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "AdminFunc/AdminFunc.h"
#include "UserFunc/UserFunc.h"

int main()
{
    int escolha;

    printf("Administrador - 1\n");
    printf("Usuário - 2\n");
    printf("Escolha: ");

    scanf("%i", &escolha);

    if (escolha == 1)
    {
        AdminFunc();
    }
    else if (escolha == 2)
    {
        UserFunc();
    }
    else
    {
    printf("Opção inválida");
    }

    return 0;
}