#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int id;
    char nome[100];
    char email[100];
    char senha[50];
} Admin;

typedef struct {
    int id;
    char nome[100];
    char email[100];
    char senha[50];
    char telefone[20];
    char nomeAluno[100];
    int vanId;
} User;

#endif