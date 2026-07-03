#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Senha {
    int numero;
    char tipo;
    char horario[6];
    struct Senha *prox;
} Senha;

typedef struct {
    Senha *inicio;
    Senha *fim;
    int quantidade;
} FilaNormal;

typedef struct {
    Senha *fim;
    int quantidade;
} FilaCircular;

FilaNormal filaN = {NULL, NULL, 0};
FilaCircular filaP = {NULL, 0};

int contadorSenhaN = 0;
int contadorSenhaP = 0;
int ciclo = 0;

void pegarHorarioAtual(char *destino) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(destino, 6, "%H:%M", tm_info);
}

Senha *criarSenha(int numero, char tipo) {
    Senha *nova = (Senha *) malloc(sizeof(Senha));
    if (nova == NULL) {
        printf("Erro: memoria insuficiente!\n");
        exit(1);
    }
    nova->numero = numero;
    nova->tipo = tipo;
    pegarHorarioAtual(nova->horario);
    nova->prox = NULL;
    return nova;
}

void enfileirarNormal() {
    contadorSenhaN++;
    Senha *nova = criarSenha(contadorSenhaN, 'N');

    if (filaN.inicio == NULL) {
        filaN.inicio = nova;
        filaN.fim = nova;
    } else {
        filaN.fim->prox = nova;
        filaN.fim = nova;
    }
    filaN.quantidade++;
    printf("Senha NORMAL N%03d cadastrada as %s.\n", nova->numero, nova->horario);
}

int filaNormalVazia() {
    return filaN.quantidade == 0;
}

Senha *atenderNormal() {
    if (filaNormalVazia()) return NULL;

    Senha *atendido = filaN.inicio;
    filaN.inicio = filaN.inicio->prox;
    if (filaN.inicio == NULL) {
        filaN.fim = NULL;
    }
    filaN.quantidade--;
    return atendido;
}

void enfileirarPreferencial() {
    contadorSenhaP++;
    Senha *nova = criarSenha(contadorSenhaP, 'P');

    if (filaP.fim == NULL) {

        nova->prox = nova;
        filaP.fim = nova;
    } else {

        nova->prox = filaP.fim->prox;
        filaP.fim->prox = nova;
        filaP.fim = nova;
    }
    filaP.quantidade++;
    printf("Senha PREFERENCIAL P%03d cadastrada as %s.\n", nova->numero, nova->horario);
}

int filaPreferencialVazia() {
    return filaP.quantidade == 0;
}

Senha *atenderPreferencial() {
    if (filaPreferencialVazia()) return NULL;

    Senha *inicio = filaP.fim->prox;

    if (filaP.fim == inicio) {

        filaP.fim = NULL;
    } else {
        filaP.fim->prox = inicio->prox;
    }
    filaP.quantidade--;

    inicio->prox = NULL;
    return inicio;
}

void chamarProximaSenha() {
    Senha *atendido = NULL;

    if (filaNormalVazia() && filaPreferencialVazia()) {
        printf("\nNao ha senhas em nenhuma das filas.\n");
        return;
    }


    if (!filaNormalVazia() && !filaPreferencialVazia()) {
        if (ciclo < 2) {
            atendido = atenderNormal();
            ciclo++;
        } else {
            atendido = atenderPreferencial();
            ciclo = 0;
        }
    }

    else if (!filaNormalVazia()) {
        atendido = atenderNormal();
    }
    else if (!filaPreferencialVazia()) {
        atendido = atenderPreferencial();
    }

    if (atendido != NULL) {
        printf("\n>> Chamando senha %c%03d (chegou as %s)\n",
               atendido->tipo, atendido->numero, atendido->horario);
        free(atendido);
    }
}

void listarFilas() {
    printf("\n--- FILA NORMAL (%d senha(s)) ---\n", filaN.quantidade);
    if (filaNormalVazia()) {
        printf("(vazia)\n");
    } else {
        Senha *atual = filaN.inicio;
        while (atual != NULL) {
            printf("N%03d - chegada: %s\n", atual->numero, atual->horario);
            atual = atual->prox;
        }
    }

    printf("\n--- FILA PREFERENCIAL (%d senha(s)) ---\n", filaP.quantidade);
    if (filaPreferencialVazia()) {
        printf("(vazia)\n");
    } else {
        Senha *inicio = filaP.fim->prox;
        Senha *atual = inicio;
        int i;
        for (i = 0; i < filaP.quantidade; i++) {
            printf("P%03d - chegada: %s\n", atual->numero, atual->horario);
            atual = atual->prox;
        }
    }
    printf("\n");
}

void liberarFilas() {

    Senha *atual = filaN.inicio;
    while (atual != NULL) {
        Senha *temp = atual;
        atual = atual->prox;
        free(temp);
    }


    if (!filaPreferencialVazia()) {
        Senha *inicio = filaP.fim->prox;
        Senha *atualP = inicio;
        int i, qtd = filaP.quantidade;
        for (i = 0; i < qtd; i++) {
            Senha *temp = atualP;
            atualP = atualP->prox;
            free(temp);
        }
    }
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);
    while (getchar() != '\n');
}

void exibirMenu() {
    printf("=====================================\n");
    printf("   SISTEMA DE ATENDIMENTO BANCARIO\n");
    printf("=====================================\n");
    printf("1 - Gerar senha NORMAL\n");
    printf("2 - Gerar senha PREFERENCIAL\n");
    printf("3 - Chamar proxima senha (regra 2N:1P)\n");
    printf("4 - Listar filas\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;

    do {
        limparTela();
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        limparTela();

        switch (opcao) {
            case 1:
                enfileirarNormal();
                break;
            case 2:
                enfileirarPreferencial();
                break;
            case 3:
                chamarProximaSenha();
                break;
            case 4:
                listarFilas();
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        if (opcao != 0) {
            pausar();
        }

    } while (opcao != 0);

    liberarFilas();
    return 0;
}
