#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Definições de Constantes ---
#define CAPACIDADE_MAXIMA 5 // Tamanho fixo da fila de peças futuras
#define TIPOS_PECAS 4       // Número de tipos de peças ('I', 'O', 'T', 'L')

// --- Estrutura da Peça (Struct) ---
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L', etc.)
    int id;    // Identificador único da peça
} Peca;

// --- Variáveis Globais de Controle da Fila ---
Peca filaPecas[CAPACIDADE_MAXIMA]; // Array que armazena as peças
int frente = 0;                    // Índice do primeiro elemento (dequeue)
int fim = 0;                       // Índice da próxima posição livre (enqueue)
int contadorPecas = 0;             // Contador para rastrear o número de elementos na fila
int proximoId = 0;                 // ID único sequencial para novas peças

// --- Protótipos das Funções ---
Peca gerarPeca();
void inicializarFila();
int filaCheia();
int filaVazia();
void enfileirar(Peca novaPeca);
Peca desenfileirar();
void exibirFila();
void exibirMenu();

// -------------------------------------------------------------------
// ---------------------- FUNÇÕES DE LÓGICA --------------------------
// -------------------------------------------------------------------

/**
 * @brief Gera uma nova peça com tipo aleatório e ID único.
 * @return Peca: A nova peça gerada.
 */
Peca gerarPeca() {
    Peca nova;
    // Tipos de peças disponíveis
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    // Sorteia um tipo de peça aleatoriamente
    int indiceTipo = rand() % TIPOS_PECAS;
    nova.nome = tipos[indiceTipo];
    
    // Atribui o ID único e incrementa o contador global de IDs
    nova.id = proximoId;
    proximoId++;
    
    printf("\n[GERADO]: Nova peça '%c' com ID %d.\n", nova.nome, nova.id);
    return nova;
}

/**
 * @brief Inicializa a fila preenchendo-a com peças iniciais.
 */
void inicializarFila() {
    printf(">> 🚀 Inicializando a Fila de Peças Futures (Capacidade: %d)...\n", CAPACIDADE_MAXIMA);
    
    // Preenche a fila até a capacidade máxima
    for (int i = 0; i < CAPACIDADE_MAXIMA; i++) {
        Peca p = gerarPeca();
        enfileirar(p);
    }
    printf(">> ✅ Fila inicializada e preenchida.\n");
}

/**
 * @brief Verifica se a fila circular está cheia.
 * @return int: 1 (cheia) ou 0 (não cheia).
 */
int filaCheia() {
    return contadorPecas == CAPACIDADE_MAXIMA;
}

/**
 * @brief Verifica se a fila circular está vazia.
 * @return int: 1 (vazia) ou 0 (não vazia).
 */
int filaVazia() {
    return contadorPecas == 0;
}

/**
 * @brief Adiciona uma peça ao final da fila (Enqueue).
 * @param novaPeca A peça a ser inserida.
 */
void enfileirar(Peca novaPeca) {
    if (filaCheia()) {
        printf("\n[ERRO]: A fila de peças está cheia! Não é possível inserir.\n");
        return;
    }
    
    // Insere a peça na posição 'fim'
    filaPecas[fim] = novaPeca;
    
    // Atualiza o índice 'fim' (avança e garante a circularidade com o operador módulo)
    fim = (fim + 1) % CAPACIDADE_MAXIMA;
    
    // Incrementa o contador de peças na fila
    contadorPecas++;
    
    printf("\n[INSERIDO]: Peça [%c %d] adicionada ao final da fila.\n", novaPeca.nome, novaPeca.id);
}

/**
 * @brief Remove a peça da frente da fila (Dequeue) e a retorna.
 * @return Peca: A peça removida.
 */
Peca desenfileirar() {
    if (filaVazia()) {
        printf("\n[ERRO]: A fila de peças está vazia! Não há peça para jogar.\n");
        // Retorna uma peça nula/vazia para sinalizar erro
        Peca vazia = {'X', -1}; 
        return vazia; 
    }
    
    // Pega a peça da posição 'frente'
    Peca pecaRemovida = filaPecas[frente];
    
    // Atualiza o índice 'frente' (avança e garante a circularidade)
    frente = (frente + 1) % CAPACIDADE_MAXIMA;
    
    // Decrementa o contador de peças
    contadorPecas--;
    
    printf("\n[JOGADA]: Peça [%c %d] removida da frente (dequeue).\n", pecaRemovida.nome, pecaRemovida.id);
    return pecaRemovida;
}

// -------------------------------------------------------------------
// ---------------------- FUNÇÕES DE INTERFACE -----------------------
// -------------------------------------------------------------------

/**
 * @brief Exibe o estado atual da fila de peças.
 */
void exibirFila() {
    printf("\n--- ESTADO ATUAL DA FILA DE PEÇAS ---\n");
    printf("Total de Peças: %d / %d\n", contadorPecas, CAPACIDADE_MAXIMA);
    
    if (filaVazia()) {
        printf("A fila está vazia.\n");
        return;
    }
    
    printf("Fila de peças: ");
    
    // Percorre a fila a partir da 'frente' até o 'fim'
    int i = frente;
    for (int count = 0; count < contadorPecas; count++) {
        printf("[%c %d]", filaPecas[i].nome, filaPecas[i].id);
        
        // Avança o índice, mantendo a circularidade
        i = (i + 1) % CAPACIDADE_MAXIMA;
        
        // Adiciona uma seta se não for o último elemento
        if (count < contadorPecas - 1) {
            printf(" -> ");
        }
    }
    printf("\n-------------------------------------\n");
}

/**
 * @brief Exibe o menu de opções para o jogador.
 */
void exibirMenu() {
    printf("\n--- OPÇÕES DE AÇÃO ---\n");
    printf("Código | Ação\n");
    printf("-------|------------------------------\n");
    printf("   1   | Jogar peça (dequeue)\n");
    printf("   2   | Inserir nova peça (enqueue)\n");
    printf("   0   | Sair\n");
    printf("------------------------------------\n");
    printf("Escolha uma opção: ");
}

// -------------------------------------------------------------------
// ------------------------- FUNÇÃO PRINCIPAL ------------------------
// -------------------------------------------------------------------

int main() {
    // Inicializa a semente para números aleatórios (usado em gerarPeca)
    srand(time(NULL));
    
    int opcao;
    
    // 1. Inicialização da fila de peças
    inicializarFila();
    exibirFila();
    
    // 2. Loop principal de interação
    do {
        exibirMenu();
        
        // Verifica se a leitura da opção foi bem sucedida
        if (scanf("%d", &opcao) != 1) {
            printf("\n[AVISO]: Entrada inválida. Tente novamente.\n");
            // Limpa o buffer de entrada para evitar loop infinito em caso de erro
            while (getchar() != '\n'); 
            continue;
        }
        
        switch (opcao) {
            case 1: // Jogar Peça (Dequeue)
                desenfileirar();
                break;
                
            case 2: { // Inserir Nova Peça (Enqueue)
                Peca nova = gerarPeca();
                enfileirar(nova);
                break;
            }
                
            case 0: // Sair
                printf("\n>> 🚪 Saindo do Tetris Stack Simulator. Até mais!\n");
                break;
                
            default: // Opção Inválida
                printf("\n[AVISO]: Opção desconhecida. Por favor, escolha 0, 1 ou 2.\n");
        }
        
        // Exibe o estado da fila após cada ação, exceto ao sair
        if (opcao != 0) {
            exibirFila();
        }
        
    } while (opcao != 0);

    return 0;
}