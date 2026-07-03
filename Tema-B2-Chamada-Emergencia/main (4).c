//maioria dos comentarios foram feitos para guiar e auxiliar
// tanto a explicacao para meu grupo tanto para 
//ajudar no video 
//entao peço perdao caso nao esteja seguindo algum padrao

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // implementei para usar disso pra poder usar a funcao sleep()

// struct chamada
struct Chamada {
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
};

// no da lista encadeada
struct No {
    struct Chamada dados;
    struct No *prox;
};

// topo da pilha agora e um ponteiro pro primeiro no
struct No *topo = NULL;

int qtdAtendidas = 0;


void limparEnter() {
    while (getchar() != '\n');
}

int existeProtocolo(int p) {
    struct No *atual = topo;

    // percorro a lista toda comparando o protocolo
    while (atual != NULL) {
        if (atual->dados.protocolo == p) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void registrarChamada() {
    struct No *novoNo;
    int protocoloDigitado;

    printf("\nDigite o protocolo (numero): ");
    scanf("%d", &protocoloDigitado);
    limparEnter();

    if (existeProtocolo(protocoloDigitado)) {
        printf("Esse protocolo ja existe na pilha! Tente outro numero.\n");
        return;
    }

    // aloco memoria pra um no novo (malloc)
    novoNo = (struct No *) malloc(sizeof(struct No));

    if (novoNo == NULL) {
        printf("\nNao consegui alocar memoria, tenta de novo.\n");
        return;
    }

    novoNo->dados.protocolo = protocoloDigitado;

    printf("Local da emergencia: ");
    fgets(novoNo->dados.local, 50, stdin);
    novoNo->dados.local[strcspn(novoNo->dados.local, "\n")] = '\0';

    printf("Tipo de ocorrencia: ");
    fgets(novoNo->dados.tipo, 30, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';

    printf("Horario (ex: 14:30): ");
    fgets(novoNo->dados.horario, 20, stdin);
    novoNo->dados.horario[strcspn(novoNo->dados.horario, "\n")] = '\0';

    // aqui e o push: o no novo aponta pro topo antigo, e vira o topo novo
    novoNo->prox = topo;
    topo = novoNo;

    printf("\nChamada registrada com sucesso! (protocolo %d)\n", protocoloDigitado);
}

void atenderChamada() {
    struct No *noRemovido;

    if (topo == NULL) {
        printf("\nNao tem nenhuma chamada para atender, pilha vazia!\n");
        return;
    }

    printf("\nAtendendo chamada do topo:\n");
    printf("Protocolo: %d\n", topo->dados.protocolo);
    printf("Local: %s\n", topo->dados.local);
    printf("Tipo: %s\n", topo->dados.tipo);
    printf("Horario: %s\n", topo->dados.horario);

    // guardo o no atual numa variavel auxiliar antes de mexer no topo
    noRemovido = topo;

    // ando o topo pro proximo no da lista
    topo = topo->prox;

    // so agora que posso liberar o no antigo, porque ja copiei
    // tudo que precisava e ja andei o ponteiro do topo
    free(noRemovido);

    qtdAtendidas++;

    printf("\nChamada atendida e removida da pilha.\n");
}

void verTopoDaPilha() {
    if (topo == NULL) {
        printf("\nA pilha esta vazia, nao tem chamada no topo.\n");
        return;
    }

    printf("\nProxima chamada a ser atendida (topo da pilha):\n");
    printf("Protocolo: %d\n", topo->dados.protocolo);
    printf("Local: %s\n", topo->dados.local);
    printf("Tipo: %s\n", topo->dados.tipo);
    printf("Horario: %s\n", topo->dados.horario);
}

void listarPilha() {
    struct No *atual = topo;
    int cont = 0;

    if (topo == NULL) {
        printf("\nPilha vazia, nao tem chamadas registradas.\n");
        return;
    }

    printf("\nChamadas na pilha (do topo ate a base):\n");
    printf("Protocolo | Local | Tipo | Horario\n");

    
    while (atual != NULL) {
        printf("%d | %s | %s | %s\n",
               atual->dados.protocolo, atual->dados.local,
               atual->dados.tipo, atual->dados.horario);
        cont++;
        atual = atual->prox;
    }

    printf("Total de chamadas na pilha: %d\n", cont);
}

// libera todos os nos da lista (usada no carregar e no sair)
void liberarPilha() {
    struct No *aux;

    while (topo != NULL) {
        aux = topo;
        topo = topo->prox;
        free(aux);
    }
}

// funcao recursiva so pra ajudar a salvar o arquivo na ordem certa.
// ela desce ate o fim da lista (a base) primeiro, e so na volta
// que vai escrevendo no arquivo. Por isso o arquivo fica com a
// base em cima e o topo embaixo, igual no exemplo do enunciado.
void salvarNoNoArquivo(FILE *arq, struct No *n) {
    if (n == NULL) {
        return;
    }

    salvarNoNoArquivo(arq, n->prox); // primeiro vai ate a base

    // isso so roda depois que voltou da chamada recursiva,
    // entao escreve de tras pra frente (base -> topo)
    fprintf(arq, "%d;%s;%s;%s\n",
            n->dados.protocolo, n->dados.local, n->dados.tipo, n->dados.horario);
}

void salvarCSV() {
    FILE *arq;

    arq = fopen("chamadas.csv", "w");
    if (arq == NULL) {
        printf("\nDeu erro para abrir o arquivo.\n");
        return;
    }

    fprintf(arq, "protocolo;local;tipo;horario\n");
    salvarNoNoArquivo(arq, topo);

    fclose(arq);
    printf("\nArquivo chamadas.csv salvo com sucesso!\n");
}

void carregarCSV() {
    FILE *arq;
    char linha[200];
    int primeira = 1;

    arq = fopen("chamadas.csv", "r");
    if (arq == NULL) {
        printf("\nNao encontrei o arquivo chamadas.csv.\n");
        return;
    }

    // libero a pilha atual antes de carregar os dados novos,
    // senao ia vazar memoria (ficar com nos "perdidos" sem free)
    liberarPilha();

    while (fgets(linha, sizeof(linha), arq) != NULL) {

        if (primeira == 1) {
            primeira = 0; // pula o cabecalho
            continue;
        }

        struct No *novoNo;
        char *pedaco;

        linha[strcspn(linha, "\n")] = '\0';

        novoNo = (struct No *) malloc(sizeof(struct No));
        if (novoNo == NULL) {
            printf("\nNao consegui alocar memoria pra carregar o arquivo todo.\n");
            break;
        }

        pedaco = strtok(linha, ";");
        novoNo->dados.protocolo = atoi(pedaco);

        pedaco = strtok(NULL, ";");
        strcpy(novoNo->dados.local, pedaco);

        pedaco = strtok(NULL, ";");
        strcpy(novoNo->dados.tipo, pedaco);

        pedaco = strtok(NULL, ";");
        strcpy(novoNo->dados.horario, pedaco);

        // como o arquivo esta na ordem base -> topo, empilhando
        // cada linha na ordem que eu leio ja reconstroi a pilha certinha
        novoNo->prox = topo;
        topo = novoNo;
    }

    fclose(arq);
    printf("\nDados carregados do arquivo com sucesso!\n");
}
// particularmente adicionei um sleep e clear 
// Pois ao usar por bantante tempo acaba poluindo
// muito a tela pro usuario

void pausarTela() {
    printf("\n(voltando ao menu...)\n");
    sleep(3); // espera 2 segundos pode aumentar se achar pouco tempo
    system("clear"); 
    
}

int main() {
    int opcao;

    do {
        printf("\n===== CENTRAL DE EMERGENCIA =====\n");
        printf("1 - Registrar chamada\n");
        printf("2 - Atender chamada\n");
        printf("3 - Ver topo da pilha\n");
        printf("4 - Listar chamadas\n");
        printf("5 - Salvar em CSV\n");
        printf("6 - Carregar do CSV\n");
        printf("7 - Quantas ja foram atendidas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        limparEnter();

        if (opcao == 1) {
            registrarChamada();
        } else if (opcao == 2) {
            atenderChamada();
        } else if (opcao == 3) {
            verTopoDaPilha();
        } else if (opcao == 4) {
            listarPilha();
        } else if (opcao == 5) {
            salvarCSV();
        } else if (opcao == 6) {
            carregarCSV();
        } else if (opcao == 7) {
            printf("\nTotal de chamadas atendidas: %d\n", qtdAtendidas);
        } else if (opcao == 0) {
            printf("\nSaindo do programa...\n");
        } else {
            printf("\nOpcao invalida, tenta de novo.\n");
        }

        
        if (opcao != 0) {
            pausarTela();
        }

    } while (opcao != 0);

     // antes de fechar o programa, usa free para todos os nos que sobraram
    // na pilha, pra nao deixar memoria vazando
    liberarPilha();

    return 0;
}