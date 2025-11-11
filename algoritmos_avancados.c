#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de cada sala (Nó da Árvore)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda; // Caminho para a sala à esquerda
    struct Sala *direita;  // Caminho para a sala à direita
} Sala;

/**
 * @brief Aloca e inicializa uma nova sala.
 * @param nome O nome da nova sala.
 * @param esquerda O ponteiro para a sala à esquerda (ou NULL).
 * @param direita O ponteiro para a sala à direita (ou NULL).
 * @return O ponteiro para a nova sala criada.
 */
Sala* criarSala(const char *nome, Sala *esquerda, Sala *direita) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a sala");
        exit(EXIT_FAILURE);
    }
    // Copia o nome da sala
    strncpy(novaSala->nome, nome, sizeof(novaSala->nome) - 1);
    novaSala->nome[sizeof(novaSala->nome) - 1] = '\0'; // Garantir terminação nula
    
    novaSala->esquerda = esquerda;
    novaSala->direita = direita;
    return novaSala;
}

/**
 * @brief Libera a memória de toda a árvore (limpeza).
 * @param raiz O ponteiro para a raiz da subárvore a ser liberada.
 */
void liberarArvores(Sala *raiz) {
    if (raiz != NULL) {
        liberarArvores(raiz->esquerda);
        liberarArvores(raiz->direita);
        printf("Liberando: %s\n", raiz->nome);
        free(raiz);
    }
}

/**
 * @brief Função principal de exploração interativa da mansão.
 * @param raiz O ponteiro para o Hall de Entrada (raiz da árvore).
 */
void explorarSalas(Sala *raiz) {
    Sala *atual = raiz;
    char escolha;

    printf("\n--- Bem-vindo à Mansão Mistério! ---\n");
    printf("Você está no %s.\n", atual->nome);

    // Loop principal de exploração
    while (atual != NULL) {
        // Verifica se a sala atual é um nó-folha (fim do caminho)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n Fim do Caminho! Esta sala não tem mais portas.\n");
            break; 
        }

        // Exibe opções de navegação
        printf("\nOnde deseja ir? ");
        if (atual->esquerda != NULL) {
            printf("(**e** - Esquerda: %s)", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            if (atual->esquerda != NULL) printf(" | ");
            printf("(**d** - Direita: %s)", atual->direita->nome);
        }
        printf(" | (**s** - Sair)\n");
        printf("Sua escolha: ");
        
        // Leitura da escolha do usuário
        if (scanf(" %c", &escolha) != 1) {
            // Lidar com erro de leitura (raro)
            break; 
        }

        // Processamento da escolha
        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
                printf("\nVocê entrou no **%s**.\n", atual->nome);
            } else {
                printf("\n Não há sala à esquerda. Tente outra direção.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
                printf("\nVocê entrou no **%s**.\n", atual->nome);
            } else {
                printf("\n Não há sala à direita. Tente outra direção.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("\n Saindo da exploração. Até a próxima!\n");
            break;
        } else {
            printf("\n Opção inválida. Use 'e', 'd' ou 's'.\n");
        }
    }
    
    if (atual == NULL) {
        printf("\nErro na exploração: o ponteiro da sala atual é NULL.\n");
    }
}

// --------------------- FUNÇÃO PRINCIPAL ---------------------
int main() {
    // 1. Definição estática da Árvore Binária da Mansão
    // Criando os nós-folha (nível mais baixo)
    Sala *sala_segredos = criarSala("Sala dos Segredos", NULL, NULL);
    Sala *jardim_inverno = criarSala("Jardim de Inverno", NULL, NULL);
    Sala *deposito = criarSala("Depósito de Velharias", NULL, NULL);
    Sala *quarto_crianca = criarSala("Quarto da Criança", NULL, NULL);

    // Nível intermediário (filhos apontam para os nós-folha)
    Sala *biblioteca = criarSala("Biblioteca Antiga", sala_segredos, jardim_inverno);
    Sala *escritorio = criarSala("Escritório do Mordomo", deposito, quarto_crianca);

    // Nível superior (filhos apontam para os nós intermediários)
    Sala *sala_jantar = criarSala("Sala de Jantar", NULL, escritorio);
    Sala *corredor = criarSala("Corredor Principal", biblioteca, sala_jantar);

    // Raiz da Árvore (Início da Exploração)
    Sala *hall_entrada = criarSala("Hall de Entrada", corredor, NULL); // Apenas Corredor à esquerda

    printf("Mapa da Mansão (Árvore Binária) Criado com Sucesso!\n");
    // 

    // 2. Iniciar a Exploração
    explorarSalas(hall_entrada);

    // 3. Limpeza de Memória
    liberarArvores(hall_entrada);

    return 0;
}
