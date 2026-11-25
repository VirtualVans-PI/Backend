# VirtualVans — Backend

Backend do **VirtualVans**, desenvolvido como parte do Projeto Integrador do curso de Análise e Desenvolvimento de Sistemas (ADS).

## Sobre o projeto

O VirtualVans é um sistema voltado ao gerenciamento do transporte escolar da Van da Tia Cláudia.

O objetivo é centralizar e organizar informações que atualmente são controladas manualmente ou por diferentes meios, como WhatsApp e planilhas, facilitando o gerenciamento de usuários e vans.

Neste semestre, o foco do desenvolvimento é construir a base funcional do sistema em linguagem C, com recursos de cadastro, consulta, alteração e exclusão de registros, além do armazenamento dos dados e do relacionamento entre usuários e veículos.

## Tecnologias utilizadas

- Linguagem C
- GCC
- Make
- Git e GitHub

## Funcionalidades implementadas

- Cadastro, listagem, edição e exclusão de usuários.
- Listagem de usuários e vans pelos módulos de gerenciamento correspondentes.
- Armazenamento de dados em arquivos CSV.
- Organização do código em módulos.
- Compilação automatizada por meio de um `Makefile`.

## Estrutura do projeto

```text
VirtualVans/
├── .vscode/
│   └── arquivos de configuração
├── AdminFunc/
│   ├── GerenciarUsuarios/
│   ├── GerenciarVans/
│   ├── AdminFunc.c
│   └── AdminFunc.h
├── UserFunc/
│   ├── UserFunc.c
│   └── UserFunc.h
├── dados/
│   ├── usuarios.csv
│   └── vans.csv
├── .gitignore
├── main.c
├── Makefile
├── README.md
└── structs.h
```

Os módulos `GerenciarUsuarios` e `GerenciarVans` concentram as funcionalidades relacionadas ao gerenciamento de usuários e vans, respectivamente.

## Pré-requisitos

Para compilar e executar o projeto, é necessário ter:

- GCC
- Make
- Um terminal compatível com os comandos utilizados

No macOS, o GCC compatível e o Make podem ser instalados por meio das ferramentas de linha de comando do Xcode.

## Como compilar e executar

Na raiz do projeto, execute:

```bash
make
```

Para iniciar o programa:

```bash
./main
```

Para remover o executável gerado:

```bash
make clean
```

## Armazenamento dos dados

Os dados são armazenados em arquivos CSV dentro da pasta `dados/`:

- `usuarios.csv`: registros de usuários.
- `vans.csv`: registros de vans.

**Importante:** utilize apenas dados fictícios no repositório. As senhas atualmente são armazenadas em texto puro, portanto esta implementação é destinada ao desenvolvimento acadêmico e não deve ser utilizada em produção sem melhorias de segurança.

## Próximas etapas

As funcionalidades abaixo fazem parte da evolução planejada do projeto e não devem ser consideradas implementadas apenas por estarem listadas aqui:

- Aprimoramento do controle de acesso por perfil.
- Gerenciamento completo de vans e relacionamento entre usuários e veículos.
- Acompanhamento de rotas por GPS.
- Controle de pagamentos e presença.
- Envio de notificações e integração com serviços externos.

## Equipe

Projeto desenvolvido por estudantes do curso de Análise e Desenvolvimento de Sistemas, como parte do Projeto Integrador.

Integrantes:

- Lucas Couto
- Gustavo Ferreira
- Willen Favarin
