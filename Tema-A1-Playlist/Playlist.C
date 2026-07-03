#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MUSICAS 100

// ============================================================================
// STRUCTS E ESTRUTURAS DE DADOS
// ============================================================================


typedef struct {
    int id;
    char titulo[100];
    char artista[100];
    char duracao[10]; // Ex: "3:45"
    char genero[50];
} Musica;


typedef struct Node {
    Musica dado;
    struct Node* proximo;
} Node;


void limparBuffer();
void removerNovaLinha(char *string);


int verificarIdUnicoVetor(Musica vetor[], int qtd, int id);
void cadastrarVetor(Musica vetor[], int *qtd);
void buscarVetor(Musica vetor[], int qtd);
void editarVetor(Musica vetor[], int qtd);
void excluirVetor(Musica vetor[], int *qtd);
void listarVetor(Musica vetor[], int qtd);
void menuVetor(Musica vetor[], int *qtd);


int verificarIdUnicoDinamico(Node* inicio, int id);
void cadastrarDinamico(Node** inicio);
void buscarDinamico(Node* inicio);
void editarDinamico(Node* inicio);
void excluirDinamico(Node** inicio);
void listarDinamico(Node* inicio);
void liberarListaDinamica(Node* inicio);
void menuDinamico(Node** inicio);


int main() {
    Musica vetor[MAX_MUSICAS];
    int qtdVetor = 0;
    Node* listaDinamica = NULL;
    
    int opcaoModo;

    do {
        printf("\n=========================================\n");
        printf("       SISTEMA DE PLAYLIST (C99)         \n");
        printf("=========================================\n");
        printf("[1] Executar Modo Vetor Estático (Obrigatório)\n");
        printf("[2] Executar Modo Alocação Dinâmica (Extra)\n");
        printf("[0] Sair do Programa\n");
        printf("Escolha uma opção de armazenamento: ");
        if (scanf("%d", &opcaoModo) != 1) {
            limparBuffer();
            opcaoModo = -1;
        }

        switch (opcaoModo) {
            case 1:
                menuVetor(vetor, &qtdVetor);
                break;
            case 2:
                menuDinamico(&listaDinamica);
                break;
            case 0:
                printf("\nEncerrando o programa. Até logo!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcaoModo != 0);

    
    liberarListaDinamica(listaDinamica);
    return 0;
}


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerNovaLinha(char *string) {
    size_t len = strlen(string);
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }
}

int verificarIdUnicoVetor(Musica vetor[], int qtd, int id) {
    for (int i = 0; i < qtd; i++) {
        if (vetor[i].id == id) return 0; // Já existe
    }
    return 1; // É único
}

void cadastrarVetor(Musica vetor[], int *qtd) {
    if (*qtd >= MAX_MUSICAS) {
        printf("\n[Erro] A playlist em vetor está cheia!\n");
        return;
    }

    Musica nova;
    printf("\n--- Cadastrar Música (Vetor) ---\n");
    printf("Digite o ID (único): ");
    scanf("%d", &nova.id);
    limparBuffer();

    if (!verificarIdUnicoVetor(vetor, *qtd, nova.id)) {
        printf("\n[Erro] Já existe uma música cadastrada com este ID!\n");
        return;
    }

    printf("Título: ");
    fgets(nova.titulo, sizeof(nova.titulo), stdin);
    removerNovaLinha(nova.titulo);

    printf("Artista: ");
    fgets(nova.artista, sizeof(nova.artista), stdin);
    removerNovaLinha(nova.artista);

    printf("Duração (ex: 3:45): ");
    fgets(nova.duracao, sizeof(nova.duracao), stdin);
    removerNovaLinha(nova.duracao);

    printf("Gênero: ");
    fgets(nova.genero, sizeof(nova.genero), stdin);
    removerNovaLinha(nova.genero);

    vetor[*qtd] = nova;
    (*qtd)++;
    printf("\nMúsica cadastrada com sucesso no vetor!\n");
}

void buscarVetor(Musica vetor[], int qtd) {
    if (qtd == 0) {
        printf("\nA playlist está vazia.\n");
        return;
    }

    int id;
    printf("\nDigite o ID da música que deseja buscar: ");
    scanf("%d", &id);

    for (int i = 0; i < qtd; i++) {
        if (vetor[i].id == id) {
            printf("\nMúsica Encontrada:\n");
            printf("ID: %d | %s - %s [%s] (%s)\n", vetor[i].id, vetor[i].titulo, vetor[i].artista, vetor[i].genero, vetor[i].duracao);
            return;
        }
    }
    printf("\nMúsica com ID %d não encontrada.\n", id);
}

void editarVetor(Musica vetor[], int qtd) {
    if (qtd == 0) {
        printf("\nA playlist está vazia.\n");
        return;
    }

    int id;
    printf("\nDigite o ID da música que deseja editar: ");
    scanf("%d", &id);
    limparBuffer();

    for (int i = 0; i < qtd; i++) {
        if (vetor[i].id == id) {
            printf("\nEditando os dados da música (O ID não pode ser alterado):\n");
            
            printf("Novo Título: ");
            fgets(vetor[i].titulo, sizeof(vetor[i].titulo), stdin);
            removerNovaLinha(vetor[i].titulo);

            printf("Novo Artista: ");
            fgets(vetor[i].artista, sizeof(vetor[i].artista), stdin);
            removerNovaLinha(vetor[i].artista);

            printf("Nova Duração: ");
            fgets(vetor[i].duracao, sizeof(vetor[i].duracao), stdin);
            removerNovaLinha(vetor[i].duracao);

            printf("Novo Gênero: ");
            fgets(vetor[i].genero, sizeof(vetor[i].genero), stdin);
            removerNovaLinha(vetor[i].genero);

            printf("\nMúsica atualizada com sucesso!\n");
            return;
        }
    }
    printf("\nMúsica com ID %d não encontrada.\n", id);
}

void excluirVetor(Musica vetor[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA playlist está vazia.\n");
        return;
    }

    int id;
    printf("\nDigite o ID da música que deseja excluir: ");
    scanf("%d", &id);

    for (int i = 0; i < *qtd; i++) {
        if (vetor[i].id == id) {
            
            for (int j = i; j < (*qtd) - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*qtd)--;
            printf("\nMúsica excluída do vetor com sucesso!\n");
            return;
        }
    }
    printf("\nMúsica com ID %d não encontrada.\n", id);
}

void listarVetor(Musica vetor[], int qtd) {
    if (qtd == 0) {
        printf("\nA playlist em vetor está vazia.\n");
        return;
    }

    printf("\n--- Lista de Músicas (Modo Vetor) ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Músicas: %s - Artista: %s | Gênero: %s | Duração: %s\n", 
               vetor[i].id, vetor[i].titulo, vetor[i].artista, vetor[i].genero, vetor[i].duracao);
    }
}

void menuVetor(Musica vetor[], int *qtd) {
    int opcao;
    do {
        printf("\n>> MENU: MODO VETOR ESTÁTICO <<\n");
        printf("[1] Cadastrar Música\n");
        printf("[2] Buscar Música\n");
        printf("[3] Editar Música\n");
        printf("[4] Excluir Música\n");
        printf("[5] Listar Todas\n");
        printf("[0] Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1;
        }

        switch (opcao) {
            case 1: cadastrarVetor(vetor, qtd); break;
            case 2: buscarVetor(vetor, *qtd); break;
            case 3: editarVetor(vetor, *qtd); break;
            case 4: excluirVetor(vetor, qtd); break;
            case 5: listarVetor(vetor, *qtd); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

// ============================================================================
// IMPLEMENTAÇÃO: MODO ALOCAÇÃO DINÂMICA (EXTRA)
// ============================================================================
int verificarIdUnicoDinamico(Node* inicio, int id) {
    Node* atual = inicio;
    while (atual != NULL) {
        if (atual->dado.id == id) return 0; // Já existe
        atual = atual->proximo;
    }
    return 1;
}

void cadastrarDinamico(Node** inicio) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("\n[Erro] Falha de memória ao alocar nó!\n");
        return;
    }

    printf("\n--- Cadastrar Música (Dinâmico) ---\n");
    printf("Digite o ID (único): ");
    scanf("%d", &novoNo->dado.id);
    limparBuffer();

    if (!verificarIdUnicoDinamico(*inicio, novoNo->dado.id)) {
        printf("\n[Erro] Já existe uma música cadastrada com este ID!\n");
        free(novoNo);
        return;
    }

    printf("Título: ");
    fgets(novoNo->dado.titulo, sizeof(novoNo->dado.titulo), stdin);
    removerNovaLinha(novoNo->dado.titulo);

    printf("Artista: ");
    fgets(novoNo->dado.artista, sizeof(novoNo->dado.artista), stdin);
    removerNovaLinha(novoNo->dado.artista);

    printf("Duração (ex: 3:45): ");
    fgets(novoNo->dado.duracao, sizeof(novoNo->dado.duracao), stdin);
    removerNovaLinha(novoNo->dado.duracao);

    printf("Gênero: ");
    fgets(novoNo->dado.genero, sizeof(novoNo->dado.genero), stdin);
    removerNovaLinha(novoNo->dado.genero);

    novoNo->proximo = NULL;

    
    
    if (*inicio == NULL) {
        *inicio = novoNo;
    } else {
        Node* atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }

    printf("\nMúsica cadastrada com sucesso na lista encadeada!\n");
}

void buscarDinamico(Node* inicio) {
    if (inicio == NULL) {
        printf("\nA playlist dinâmica está vazia.\n");
        return;
    }

    int id;
    printf("\nDigite o ID da música que deseja buscar: ");
    scanf("%d", &id);

    Node* atual = inicio;
    while (atual != NULL) {
        if (atual->dado.id == id) {
            printf("\nMúsica Encontrada (Dinâmico):\n");
            printf("ID: %d | %s - %s [%s] (%s)\n", atual->dado.id, atual->dado.titulo, atual->dado.artista, atual->dado.genero, atual->dado.duracao);
            return;
        }
        atual = atual->proximo;
    }
    printf("\nMúsica com ID %d não encontrada.\n", id);
}

void editarDinamico(Node* inicio) {
    if (inicio == NULL) {
        printf("\nA playlist dinâmica está vazia.\n");
        return;
    }

    int id;
    printf("\nDigite o ID da música que deseja editar: ");
    scanf("%d", &id);
    limparBuffer();

    Node* atual = inicio;
    while (atual != NULL) {
        if (atual->dado.id == id) {
            printf("\nEditando os dados da música dinamicamente:\n");
            
            printf("Novo Título: ");
            fgets(atual->dado.titulo, sizeof(atual->dado.titulo), stdin);
            removerNovaLinha(atual->dado.titulo);

            printf("Novo Artista: ");
            fgets(atual->dado.artista, sizeof(atual->dado.artista), stdin);
            removerNovaLinha(atual->dado.artista);

            printf("Nova Duração: ");
            fgets(atual->dado.duracao, sizeof(atual->dado.duracao), stdin);
            removerNovaLinha(atual->dado.duracao);

            printf("Novo Gênero: ");
            fgets(atual->dado.genero, sizeof(atual->dado.genero), stdin);
            removerNovaLinha(atual->dado.genero);

            printf("\nMúsica atualizada com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("\nMúsica com ID %d não encontrada.\n", id);
}

void excluirDinamico(Node** inicio) {
    if (*inicio == NULL) {
        printf("\nA playlist dinâmica está vazia.\n");
        return;
    }

    int id;
    printf("\nDigite o ID da música que deseja excluir: ");
    scanf("%d", &id);

    Node* atual = *inicio;
    Node* anterior = NULL;

    while (atual != NULL && atual->dado.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nMúsica com ID %d não encontrada.\n", id);
        return;
    }

    
    
    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\nMúsica excluída da lista encadeada com sucesso!\n");
}

void listarDinamico(Node* inicio) {
    if (inicio == NULL) {
        printf("\nA playlist dinâmica está vazia.\n");
        return;
    }

    printf("\n--- Lista de Músicas (Modo Encadeado Dinâmico) ---\n");
    Node* atual = inicio;
    while (atual != NULL) {
        printf("ID: %d | Músicas: %s - Artista: %s | Gênero: %s | Duração: %s\n", 
               atual->dado.id, atual->dado.titulo, atual->dado.artista, atual->dado.genero, atual->dado.duracao);
        atual = atual->proximo;
    }
}

void liberarListaDinamica(Node* inicio) {
    Node* atual = inicio;
    while (atual != NULL) {
        Node* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

void menuDinamico(Node** inicio) {
    int opcao;
    do {
        printf("\n>> MENU: ALOCAÇÃO DINÂMICA <<\n");
        printf("[1] Cadastrar Música (malloc)\n");
        printf("[2] Buscar Música\n");
        printf("[3] Editar Música\n");
        printf("[4] Excluir Música (free)\n");
        printf("[5] Listar Todas\n");
        printf("[0] Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1;
        }

        switch (opcao) {
            case 1: cadastrarDinamico(inicio); break;
            case 2: buscarDinamico(*inicio); break;
            case 3: editarDinamico(*inicio); break;
            case 4: excluirDinamico(inicio); break;
            case 5: listarDinamico(*inicio); break;
            case 0: break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}
