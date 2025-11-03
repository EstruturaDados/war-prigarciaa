// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.


// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
   // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
// O número de territórios agora é definido pelo usuário (não há valor fixo)

// --- Definição da Estrutura (Struct) ---
struct Territorio {
    char nome [30];
    char cor [10];
    int tropas;
};  

// --- Função para limpar o bufer de entrada ---
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//--- Função para cadastrar território dinamicamente. ---
void cadastrarTerritorios(struct Territorio* mapa, int quant) {
    for (int i = 0; i < quant; i++) {
        printf ("\n--- Território %d ---\n", i + 1);
        printf ("Nome do território: ");
        scanf(" %29[^\n]", mapa[i].nome);
        limparBuffer();

        printf("Cor do Exército: ");
        scanf(" %9s", mapa[i].cor);
        limparBuffer();

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();      
    }
}

// --- Função para exibir todos os territórios. ---
void exibirTerritorios(struct Territorio* mapa, int quant) {
    printf("=====================================");
    printf("\n        TERRITÓRIOS ATUAIS       \n");
    printf("=====================================");

    for (int i = 0; i < quant; i++) {
        printf("\n[%d] Nome: %s\n", i + 1, mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------------\n");
    }
}

// --- Função de etaque entre territórios ---
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nDado do atacante (%s): %d", atacante->nome, dadoAtacante);
    printf("\nDado do defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor); // Muda a cor (dono)
        defensor->tropas = atacante->tropas /2; // Transfere a metade das tropas
        printf("%s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);

    } else {
        printf("\n--- RESULTADO DA BATALHA ---\n");
        printf("\nO atacante perdeu a batalha!\n");
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("%s Perdeu uma tropa! Tropas restantes: %d\n", atacante->nome, atacante->tropas);
    }

}

// --- Função para liberar a memória alocada ---
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

// --- Função Principal (main) ---
int main() {
    srand(time(NULL)); // inicializa a semente de aleatoriedade

    printf("===================================\n");
    printf("Desafio Jogo War!\n");
    printf("===================================\n");

    int quant;
    printf("\nQuantos territórios deseja cadastrar?\n");
    scanf("%d", &quant);
    limparBuffer();

      // --- Alocação dinâmica de memória ---
    struct Territorio* mapa = (struct Territorio*) calloc(quant, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        return 1;
    }

   
    // --- Cadastro e exibição inicial. ---
    cadastrarTerritorios(mapa, quant);
    exibirTerritorios(mapa, quant);

    // --- Simulação de ataque ---
    int atacante, defensor;
    printf("\nEscolha o número do território atacante (1 a %d): ", quant);
    scanf("%d", &atacante);
    printf("Escolha o número do território defensor (1 a %d): ", quant);
    scanf("%d", &defensor);

    atacante--;
    defensor--;

    // Validação: não pode atacar território da mesma cor
    if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
        printf("\nVocê não pode atacar um território do mesmo exército!\n");
    } else {
        atacar(&mapa[atacante], &mapa[defensor]);
    }

      // --- Exibição final dos territórios ---
    exibirTerritorios(mapa, quant);

    // --- Liberação de memória ---
    liberarMemoria(mapa);

    printf("\nMemória liberada com sucesso. Fim do jogo!\n");
    printf("===================================\n");
    return 0;
}



