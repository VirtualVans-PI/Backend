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

typedef struct {
    int id;
    char placa[10];
    char modelo[50];
    int capacidade;
    char motorista[100];
} Van;

#endif