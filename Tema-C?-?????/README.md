# Sistema de Atendimento Bancário — Filas Simples (Tema C1)

Simulação de um sistema de atendimento bancário com senhas **normais** e **preferenciais**, implementado em C usando **alocação dinâmica** e **listas encadeadas**.

## Estruturas utilizadas

| Fila | Implementação | Comportamento |
|---|---|---|
| Normal | Lista ligada simples | FIFO tradicional — entra no fim, sai do início |
| Preferencial | Lista circular ligada | O último nó aponta de volta para o primeiro, simulando uma fila circular |

Cada senha (`struct Senha`) guarda:
- `numero` — número sequencial da senha
- `tipo` — `'N'` (normal) ou `'P'` (preferencial)
- `horario` — horário de chegada, capturado automaticamente (`HH:MM`)
- `prox` — ponteiro para o próximo nó da fila

## Regra de atendimento

A cada chamada, o sistema segue a proporção **2 senhas normais para 1 preferencial**.

- Se as duas filas tiverem senhas, o ciclo 2N → 1P é respeitado.
- Se uma das filas estiver vazia, o atendimento continua normalmente pela fila que ainda tiver senhas, sem travar o sistema.

## Como compilar

```bash
gcc -o atendimento_bancario atendimento_bancario.c
```

## Como executar

```bash
./atendimento_bancario
```

No Windows (via MinGW/MSVC), o programa detecta o sistema automaticamente e usa `cls` no lugar de `clear` para limpar o terminal.

## Menu

```
1 - Gerar senha NORMAL
2 - Gerar senha PREFERENCIAL
3 - Chamar próxima senha (regra 2N:1P)
4 - Listar filas
0 - Sair
```

A cada opção escolhida, o terminal é limpo, o resultado da ação é exibido e o programa aguarda **ENTER** antes de voltar ao menu — assim a tela nunca fica poluída com o histórico de ações anteriores.

## Gerenciamento de memória

Todas as senhas são alocadas dinamicamente com `malloc` e liberadas com `free`:
- No momento em que a senha é atendida (removida da fila).
- Ao encerrar o programa (opção `0`), qualquer senha que ainda esteja nas filas é liberada.

## Estrutura do arquivo

- `atendimento_bancario.c` — código-fonte único, sem dependências externas (usa apenas `stdio.h`, `stdlib.h`, `string.h` e `time.h` da biblioteca padrão).
