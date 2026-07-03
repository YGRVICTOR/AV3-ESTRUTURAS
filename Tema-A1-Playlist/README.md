# 🎵 Sistema de Playlist (C99)

Sistema de gerenciamento de playlist de músicas desenvolvido em **C (padrão C99)**, implementado com **duas estruturas de dados diferentes** para fins comparativos e de estudo: vetor estático e lista encadeada com alocação dinâmica.

## 📋 Sobre o Projeto

O programa permite cadastrar, buscar, editar, excluir e listar músicas em uma playlist, através de um menu interativo no terminal. Cada música possui os seguintes atributos:

- **ID** (identificador único)
- **Título**
- **Artista**
- **Duração** (ex: `3:45`)
- **Gênero**

O usuário escolhe, a cada execução, qual modo de armazenamento deseja utilizar:

1. **Modo Vetor Estático** (obrigatório) — utiliza um array fixo (`MAX_MUSICAS = 100`) para armazenar as músicas.
2. **Modo Alocação Dinâmica** (extra) — utiliza uma lista encadeada (`struct Node`) com `malloc`/`free`, sem limite fixo de músicas (exceto pela memória disponível).

## ⚙️ Funcionalidades

Ambos os modos (Vetor e Lista Encadeada) oferecem o mesmo conjunto de operações:

| Funcionalidade | Descrição |
|---|---|
| **Cadastrar Música** | Adiciona uma nova música, validando que o ID não esteja duplicado |
| **Buscar Música** | Localiza e exibe os dados de uma música a partir do ID |
| **Editar Música** | Atualiza título, artista, duração e gênero de uma música existente (o ID não pode ser alterado) |
| **Excluir Música** | Remove uma música da playlist a partir do ID |
| **Listar Todas** | Exibe todas as músicas cadastradas |

### Recursos adicionais

- Validação de entrada numérica (evita travamentos com entradas inválidas)
- Verificação de unicidade de ID antes de cada cadastro
- Limpeza de buffer de entrada para evitar problemas com `scanf` + `fgets`
- Remoção automática do caractere de nova linha (`\n`) capturado pelo `fgets`
- Liberação de toda a memória alocada dinamicamente ao encerrar o programa (sem *memory leaks*)

## 🧠 Conceitos Demonstrados

- Structs e ponteiros para structs
- Manipulação de vetores (array de structs)
- Listas encadeadas simples (ponteiro `próximo`)
- Alocação dinâmica de memória (`malloc`, `free`)
- Passagem de parâmetros por referência (ponteiros para modificar dados fora da função)
- Modularização de código com funções bem definidas
- Menus interativos em loop (`do...while` + `switch`)

## 🚀 Como Compilar e Executar

```bash
gcc -std=c99 playlist.c -o playlist
./playlist
```

## 🖥️ Exemplo de Uso

```
=========================================
       SISTEMA DE PLAYLIST (C99)         
=========================================
[1] Executar Modo Vetor Estático (Obrigatório)
[2] Executar Modo Alocação Dinâmica (Extra)
[0] Sair do Programa
Escolha uma opção de armazenamento: 1

>> MENU: MODO VETOR ESTÁTICO <<
[1] Cadastrar Música
[2] Buscar Música
[3] Editar Música
[4] Excluir Música
[5] Listar Todas
[0] Voltar ao Menu Principal
```

## 📁 Estrutura de Dados

```c
typedef struct {
    int id;
    char titulo[100];
    char artista[100];
    char duracao[10];
    char genero[50];
} Musica;

typedef struct Node {
    Musica dado;
    struct Node* proximo;
} Node;
```

## 📌 Limitações

- Modo Vetor: capacidade máxima de **100 músicas** (`MAX_MUSICAS`)
- Modo Dinâmico: sem persistência em arquivo — os dados são perdidos ao encerrar o programa
- Não há ordenação automática das músicas cadastradas

## 📄 Licença

Projeto acadêmico/livre para fins de estudo.
