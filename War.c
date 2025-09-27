#include <stdio.h>
#include <string.h>

// --- Constantes ---
// Documentação: Usar uma constante torna o código mais fácil de manter.
// Se quisermos mudar o número de territórios, alteramos em um só lugar.
#define NUM_TERRITORIOS 5

// --- Requisito: Criação da struct ---
// Documentação: A struct 'Territorio' é definida para armazenar os dados de cada
// território do jogo. Ela agrupa três informações: o nome do território (uma string),
// a cor do exército (outra string) e a quantidade de tropas (um inteiro).
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Função para limpar o buffer de entrada ---
// Documentação: Esta função consome todos os caracteres restantes no buffer de entrada
// até encontrar uma nova linha ('\n') ou o fim do arquivo (EOF). É crucial para
// evitar que leituras anteriores (como um scanf("%d")) interfiram nas próximas
// leituras de texto (com fgets).
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Declaração do vetor de structs
    struct Territorio territorios[NUM_TERRITORIOS];
    int i; // Variável de controle para os laços

    // --- Requisito: Cadastro dos territórios ---
    printf("--- SISTEMA DE CADASTRO DE TERRITÓRIOS ---\n");
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        // Usabilidade: Agora permite nomes com espaços.
        printf("Digite o nome do território: ");
        // Segurança: fgets() é usado para evitar buffer overflow.
        // Ele lê a linha inteira, incluindo o '\n' no final.
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        // Remove o '\n' que o fgets() deixa no final da string.
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Digite a cor do exército (ex: Azul, Verde): ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        // Limpeza: Essencial após um scanf() para limpar o '\n' que ficou no buffer,
        // evitando problemas na próxima leitura com fgets().
        limpar_buffer();
    }

    // --- Requisito: Exibição dos dados ---
    printf("\n\n=========================================\n");
    printf("--- DADOS DOS TERRITÓRIOS CADASTRADOS ---\n");
    printf("=========================================\n");

    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Quantidade de Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
