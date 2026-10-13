VirtualVans — Backend

Backend do projeto **VirtualVans**, desenvolvido para o Projeto Integrador do curso de Análise e Desenvolvimento de Sistemas.

Sobre o projeto

O VirtualVans tem como objetivo auxiliar no gerenciamento do transporte escolar da Van da Tia Cláudia, facilitando a organização dos usuários e preparando a base para futuras funcionalidades do sistema.

Tecnologias utilizadas

- Linguagem C
- GCC
- Make
- Git e GitHub

Funcionalidades atuais

- Cadastro de usuários.
- Edição de usuários.
- Exclusão de usuários.
- Armazenamento dos dados em arquivo CSV.
- Organização do código em módulos.
- Compilação automatizada por meio de um `Makefile`.

Estrutura do projeto

VirtualVans/
├── .vscode/
├── AdminFunc/
│   └── GerenciarUsuarios/
├── UserFunc/
├── dados/
│   └── usuarios.csv
├── main.c
├── structs.h
├── Makefile
└── README.md

Pré-requisitos

Para compilar e executar o projeto, é necessário ter:

- GCC
- Make
- Um terminal compatível com os comandos utilizados

No macOS, o GCC compatível e o Make podem ser instalados pelas ferramentas de linha de comando do Xcode.

## Como compilar e executar

Na raiz do projeto, execute:

make

Para iniciar o programa:

./main

Para remover o executável gerado:

make clean

Armazenamento dos dados

Os dados dos usuários são armazenados no arquivo `dados/usuarios.csv`.

Importante: utilize apenas dados fictícios no repositório. As senhas atualmente são armazenadas em texto puro, portanto essa implementação é destinada ao desenvolvimento acadêmico e não deve ser utilizada em produção sem melhorias de segurança.

Próximas etapas

As funcionalidades abaixo fazem parte da evolução planejada do projeto e não devem ser consideradas implementadas apenas por estarem listadas aqui:

- Aprimoramento do controle de acesso por perfil.
- Gerenciamento de vans e relacionamento entre usuários e veículos.
- Acompanhamento de rotas por GPS.
- Integração com pagamentos.
- Envio de notificações.

Equipe

Projeto desenvolvido como parte do Projeto Integrador do curso de Análise e Desenvolvimento de Sistemas.
