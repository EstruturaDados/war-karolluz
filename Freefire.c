#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição da Struct ---
/**
 * @brief Struct para representar um item dentro do inventário.
 * Armazena informações essenciais de cada objeto coletado.
 */
typedef struct {
    char nome[30];      // Nome do item (ex: Pistola, Munição 9mm)
    char tipo[20];      // Tipo do item (ex: Arma, Municao, Cura, Ferramenta)
    int quantidade;     // Quantidade do item
} Item;

// --- Variáveis Globais para o Inventário ---
#define CAPACIDADE_MAXIMA 10 // Capacidade máxima de itens na mochila
Item inventario[CAPACIDADE_MAXIMA]; // Vetor de structs para armazenar os itens
int totalItens = 0; // Contador para o número atual de itens no inventário

// --- Protótipos das Funções ---
void menu();
void inserirItem();
void removerItem();
void listarItens();
int buscarItem(char nomeBusca[30]); // Retorna o índice do item ou -1 se não encontrado

// --- Função Principal (main) ---
int main() {
    // Inicializa o sistema e exibe o menu principal
    menu();
    return 0;
}

// --- Funções de Operação do Inventário ---

/**
 * @brief Exibe o menu principal e gerencia as opções do jogador.
 * Garante uma interface clara e orientativa.
 */
void menu() {
    int opcao;

    do {
        printf("\n--- Mochila de Loot Inicial ---\n");
        printf("1. Cadastrar Novo Item\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Buscar Item pelo Nome\n");
        printf("4. Listar Todos os Itens\n");
        printf("0. Sair do Jogo\n");
        printf("-------------------------------\n");
        printf("Escolha uma opcao: ");
        // Leitura segura da opção
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de falha na leitura (caractere não numérico)
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; // Define uma opção inválida para repetir o loop
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                // Para buscar, é necessário ler o nome e chamar a função de busca
                {
                    char nomeBusca[30];
                    printf("\nInforme o nome do item a buscar: ");
                    // Limpa o buffer antes de ler a string
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    // Leitura da string (usando fgets para maior segurança)
                    if (fgets(nomeBusca, sizeof(nomeBusca), stdin) != NULL) {
                        // Remove o newline (\n) capturado pelo fgets
                        nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                        int indice = buscarItem(nomeBusca);
                        if (indice != -1) {
                            printf("\n--- Item Encontrado ---\n");
                            printf("Nome: %s\n", inventario[indice].nome);
                            printf("Tipo: %s\n", inventario[indice].tipo);
                            printf("Quantidade: %d\n", inventario[indice].quantidade);
                            printf("----------------------\n");
                        } else {
                            printf("\n[ALERTA] Item \"%s\" nao foi encontrado na mochila.\n", nomeBusca);
                        }
                    }
                }
                break;
            case 4:
                listarItens();
                break;
            case 0:
                printf("\n[SAIDA] Salvando o inventario e saindo do jogo. Boa sorte!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida. Por favor, tente novamente.\n");
                break;
        }

        // Listagem dos itens após cada operação (requisito funcional)
        if (opcao != 0 && opcao != 3) {
            listarItens();
        }

    } while (opcao != 0);
}

/**
 * @brief Cadastra um novo item na mochila, respeitando o limite de capacidade.
 */
void inserirItem() {
    if (totalItens >= CAPACIDADE_MAXIMA) {
        printf("\n[ERRO] A mochila esta cheia! Capacidade maxima (%d) atingida.\n", CAPACIDADE_MAXIMA);
        return;
    }

    Item novoItem;

    printf("\n--- Cadastro de Novo Item ---\n");

    // Limpa o buffer antes de ler strings
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Informe o Nome do Item (max 29 caracteres): ");
    if (fgets(novoItem.nome, sizeof(novoItem.nome), stdin) != NULL) {
        // Remove o newline (\n)
        novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    } else {
        return; // Falha na leitura
    }

    printf("Informe o Tipo do Item (ex: Arma, Municao, Cura): ");
    if (fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin) != NULL) {
        // Remove o newline (\n)
        novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;
    } else {
        return; // Falha na leitura
    }

    printf("Informe a Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("\n[ERRO] Leitura de quantidade invalida. Cadastro cancelado.\n");
        // Limpa o buffer após a falha
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    // Adiciona o novo item ao final do vetor (inventario)
    inventario[totalItens] = novoItem;
    totalItens++;

    printf("\n[SUCESSO] Item '%s' cadastrado com sucesso! (%d/%d)\n", novoItem.nome, totalItens, CAPACIDADE_MAXIMA);
}

/**
 * @brief Implementa a busca sequencial.
 * @param nomeBusca O nome do item a ser procurado.
 * @return O índice do item encontrado no vetor ou -1 se não for encontrado.
 */
int buscarItem(char nomeBusca[30]) {
    // Percorre o vetor de structs do início (0) até o último item cadastrado (totalItens - 1)
    for (int i = 0; i < totalItens; i++) {
        // Comparação de strings ignorando a caixa (strcasecmp é mais robusto, mas stricmp é mais comum em C padrão,
        // vamos usar strcmp por ser padrão, mas alertar sobre a sensibilidade à caixa)
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado no índice 'i'
        }
    }
    return -1; // Item não encontrado
}

/**
 * @brief Remove um item da mochila com base no nome.
 * Utiliza a busca sequencial e, se encontrado, remove e reorganiza o vetor.
 */
void removerItem() {
    if (totalItens == 0) {
        printf("\n[ALERTA] A mochila esta vazia. Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remocao de Item ---\n");
    printf("Informe o nome do item a ser removido: ");

    // Limpa o buffer antes de ler a string
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // Leitura da string (usando fgets)
    if (fgets(nomeRemover, sizeof(nomeRemover), stdin) != NULL) {
        // Remove o newline (\n)
        nomeRemover[strcspn(nomeRemover, "\n")] = 0;
    } else {
        return; // Falha na leitura
    }

    // Busca o item no inventário
    int indice = buscarItem(nomeRemover);

    if (indice != -1) {
        // Item encontrado. Remove o item e reorganiza o vetor.
        // Move todos os elementos a partir do índice removido uma posição para trás
        for (int i = indice; i < totalItens - 1; i++) {
            inventario[i] = inventario[i + 1];
        }

        totalItens--; // Decrementa o contador de itens
        printf("\n[SUCESSO] Item '%s' removido da mochila.\n", nomeRemover);
    } else {
        printf("\n[ALERTA] Item \"%s\" nao foi encontrado na mochila. Remocao cancelada.\n", nomeRemover);
    }
}

/**
 * @brief Lista todos os itens atualmente registrados na mochila.
 */
void listarItens() {
    printf("\n======================================================\n");
    printf("             LISTAGEM ATUAL DA MOCHILA (%d/%d)             \n", totalItens, CAPACIDADE_MAXIMA);
    printf("======================================================\n");
    printf("| %-25s | %-15s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------\n");

    if (totalItens == 0) {
        printf("| %-54s |\n", "Mochila vazia! Coletar recursos URGENTE!");
        printf("======================================================\n");
        return;
    }

    // Percorre o vetor e exibe os dados de cada item
    for (int i = 0; i < totalItens; i++) {
        printf("| %-25s | %-15s | %-10d |\n",
               inventario[i].nome,
               inventario[i].tipo,
               inventario[i].quantidade);
    }
    printf("======================================================\n");
}