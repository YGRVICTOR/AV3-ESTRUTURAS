# Central de Chamadas de Emergência — Pilha (LIFO)

Simulação de uma central de chamadas de emergência usando a estrutura de dados **Pilha**, implementada com **lista encadeada** e alocação dinâmica de memória (`malloc`/`free`).

A lógica segue o comportamento LIFO (*Last In, First Out*): **a última chamada registrada é a primeira a ser atendida**.

## 📋 Descrição

Cada chamada de emergência é armazenada como um nó em uma lista encadeada. O topo da pilha é sempre a chamada mais recente:

- Ao **registrar** uma chamada, um novo nó é criado (`malloc`) e passa a ser o topo da pilha.
- Ao **atender** uma chamada, o nó do topo é removido e sua memória é liberada (`free`).
- Não há um limite fixo de chamadas — a pilha cresce dinamicamente conforme a memória disponível.

## 🗂️ Estrutura de dados

```c
struct Chamada {
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
};

struct No {
    struct Chamada dados;
    struct No *prox;
};
```

## ⚙️ Funcionalidades

| # | Funcionalidade | Descrição |
|---|---|---|
| 1 | **Registrar chamada** | Insere uma nova chamada no topo da pilha (push). Verifica se o protocolo já existe antes de inserir. |
| 2 | **Atender chamada** | Remove e exibe a chamada do topo da pilha (pop). |
| 3 | **Ver topo da pilha** | Consulta a próxima chamada a ser atendida sem removê-la (peek). |
| 4 | **Listar chamadas** | Exibe todas as chamadas atualmente na pilha, do topo até a base. |
| 5 | **Salvar em CSV** | Grava o estado atual da pilha em `chamadas.csv`, preservando a ordem correta. |
| 6 | **Carregar do CSV** | Reconstrói a pilha a partir do arquivo `chamadas.csv`. |
| 7 | **Quantas já foram atendidas** | Mostra o total de chamadas atendidas na sessão atual. |
| 0 | **Sair** | Libera toda a memória alocada e encerra o programa. |

## 🧠 Conceitos aplicados

- Pilha (estrutura LIFO)
- Lista encadeada simples
- Alocação dinâmica de memória (`malloc` / `free`)
- Recursão (usada para gravar o CSV na ordem correta)
- Manipulação de arquivos (leitura e escrita em CSV)
- Validação de estrutura vazia (evita erros ao consultar/remover pilha vazia)

## 💾 Formato do arquivo CSV

```
protocolo;local;tipo;horario
1001;Av. Paulista;Acidente;14:30
1002;Rua das Flores;Incendio;14:35
```

O arquivo é salvo da base para o topo. Ao ser recarregado, a pilha é reconstruída na ordem exata em que estava antes de ser salva.

## ▶️ Como compilar e executar

```bash
gcc -std=c99 -Wall -Wextra -o pilha_emergencia main.c
./pilha_emergencia
```

## 📌 Exemplo de uso

```
Registrar protocolo 1001
Registrar protocolo 1002
Consultar topo -> protocolo 1002
Atender        -> remove protocolo 1002
Atender        -> remove protocolo 1001
```

## 🖥️ Requisitos

- Compilador C compatível com o padrão **C99**
- Sistema operacional Linux/macOS (usa `system("clear")` para limpar o terminal — em Windows, trocar por `system("cls")`)

## 👥 Autores

Trabalho acadêmico — Estrutura de Dados (Pilha).
