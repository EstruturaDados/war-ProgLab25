#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>  
#include <string.h> 

// STRUCTS DO JOGO
typedef struct{
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército dominante
    int tropas;     // Número de tropas presentes
 }Territorio;

 typedef struct {
    char cor[10];          // Cor do exército do jogador (ex: "Azul", "Vermelho")
    char *missao;           // Ponteiro para a string da missão (alocação dinâmica)
} Jogador;

// --- PROTÓTIPOS DAS FUNÇÕES ---
Territorio* alocar_mapa(int tamanho); 
void cadastrar_territorios(Territorio* mapa, int tamanho); 
void atribuirMissao(Jogador* destino, char* missoes[], int totalMissoes);
void exibirMissao(Jogador* jogador);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* cor_jogador);
void atacar(Territorio* atacante, Territorio* defensor); 
void exibir_mapa(Territorio* mapa, int tamanho); 
void liberarMemoria(Territorio* mapa);
int ler_indice_territorio(char* prompt, int max_index);


//=================================================================
// Função Principal (MAIN): O LAÇO DO JOGO
// =================================================================
int main() {
    srand(time(NULL)); 
    
    int num_territorios;
    Territorio* mapa = NULL;
    int jogo_ativo = 1;
    
    // --- 1. CONFIGURAÇÃO INICIAL (SETUP) ---
    printf("--- CONFIGURAÇÃO INICIAL ---\n");
    printf("Digite o número total de territórios (mínimo 2): ");
    if (scanf("%d", &num_territorios) != 1 || num_territorios < 2) {
        printf("Número de territórios inválido. Encerrando.\n");
        return 1;
    }
        while (getchar() != '\n'); 
    
    mapa = alocar_mapa(num_territorios);
    if (mapa == NULL) return 1;
    
    // Cadastro de 1 Jogador e Missões
    Jogador jogador_principal = {"Vermelho", NULL};
    char* vetor_missoes[] = {
        "Dominar 5 territórios.",
        "Eliminar todas as tropas da cor Azul.",
        "Ter um total de 15 ou mais tropas.",
    };
    int total_missoes = sizeof(vetor_missoes) / sizeof(char*);
    
    atribuirMissao(&jogador_principal, vetor_missoes, total_missoes);
    cadastrar_territorios(mapa, num_territorios);

    // --- 2. LAÇO PRINCIPAL DO JOGO (GAME LOOP) ---
    do {
        int escolha_usuario;
        
        printf("\n=========================================\n");
        printf("         TURNO DO JOGADOR %s\n", jogador_principal.cor);
        printf("=========================================\n");
        
        exibir_mapa(mapa, num_territorios);
        exibirMissao(&jogador_principal);

        printf("\nMenu de Ações:\n");
        printf("1 - Iniciar Ataque\n");
        printf("2 - Verificar Vitória\n");
        printf("0 - Encerrar Jogo\n");
        printf("Sua escolha: ");
        
        if (scanf("%d", &escolha_usuario) != 1) {
            escolha_usuario = -1; // Opção inválida
            while (getchar() != '\n');
        }

        switch (escolha_usuario) {
            case 1: {
                // Rotina de Ataque
                int atacante_idx, defensor_idx;
                
                printf("\n--- FASE DE ATAQUE ---\n");
                atacante_idx = ler_indice_territorio("Escolha o território ATACANTE (número): ", num_territorios);
                defensor_idx = ler_indice_territorio("Escolha o território DEFENSOR (número): ", num_territorios);
                
             // Validação de Ataque (Atacante != Defensor, Atacante > 1 tropa)
                if (atacante_idx == defensor_idx) {
                    printf("AVISO: Você não pode atacar a si mesmo!\n");
                } else if (mapa[atacante_idx].tropas < 2) {
                    printf("AVISO: Território atacante precisa de pelo menos 2 tropas.\n");
                }
              else {
                    atacar(&mapa[atacante_idx], &mapa[defensor_idx]);
                }
                break;
            }  
              case 2:
                // Verifica se a condição de vitória foi alcançada
                if (verificarMissao(jogador_principal.missao, mapa, num_territorios, jogador_principal.cor)) {
                    printf("\n PARABÉNS! VOCÊ VENCEU O JOGO! \n");
                    jogo_ativo = 0;
                } else {
                    printf("Ainda não alcançamos a condição de vitória. Continue a luta!\n");
                }
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                jogo_ativo = 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
            }
            
          // Pausa opcional antes do próximo turno
        if (jogo_ativo) {
            printf("\n--- Pressione ENTER para continuar ---\n");
            while (getchar() != '\n'); 
        }  

       } while (jogo_ativo != 0); 

    printf("\n--- Fim do Jogo ---\n");
    
    // --- 3. LIMPEZA (CLEANUP) ---
    if (jogador_principal.missao != NULL) {
        free(jogador_principal.missao);
    }
    liberarMemoria(mapa);
    
    return 0;
}
   
// =================================================================
// FUNÇÕES DE IMPLEMENTAÇÃO (RESUMO)
// =================================================================

// Funções de Alocação e Limpeza (como as implementadas na Etapa 2)
Territorio* alocar_mapa(int tamanho) {
    Territorio* novo_mapa = (Territorio*) calloc(tamanho, sizeof(Territorio));
    if (novo_mapa == NULL) {
        printf("ERRO: Falha na alocação de memória.\n");
        return NULL; 
    }
    printf("Memória alocada dinamicamente para %d territórios.\n", tamanho);
    return novo_mapa;
}
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória do mapa liberada (free) com sucesso.\n");
    }
}

// Implementação das Funções de Missão (Etapa 3)
void atribuirMissao(Jogador* destino, char* missoes[], int totalMissoes) {
    int indice_sorteado = rand() % totalMissoes;
    char* missao_escolhida = missoes[indice_sorteado];
    
    size_t tamanho_missao = strlen(missao_escolhida) + 1;
    destino->missao = (char*) malloc(tamanho_missao);
    
    if (destino->missao != NULL) {
        strcpy(destino->missao, missao_escolhida);
        // Ajusta a cor do exército nos territórios iniciais para corresponder ao jogador
        printf("Missão sorteada para o Jogador %s.\n", destino->cor);
    } else {
        printf("ERRO: Falha ao alocar memória para a missão.\n");
    }
}
void exibirMissao(Jogador* jogador) {
    if (jogador->missao != NULL) {
        printf("\n--- MISSÃO ATUAL ---\n");
        printf("OBJETIVO: %s\n", jogador->missao);
        printf("---------------------\n");
    }
}
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* cor_jogador) {
    // Implementação Simples: Checa se dominou 5 territórios.
    if (strstr(missao, "Dominar 5 territórios") != NULL) {
        int territorios_dominados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, cor_jogador) == 0) {
                territorios_dominados++;
            }
        }
        return (territorios_dominados >= 5);
    }
    // Lógica para outras missões seria implementada aqui (ex: Eliminou a cor Azul)
    return 0; // Missão não cumprida por padrão
}

// Funções de I/O e Ataque (Implementadas na Etapa 2)
int ler_indice_territorio(char* prompt, int max_index) {
    int indice;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &indice) == 1 && indice >= 1 && indice <= max_index) {
            while (getchar() != '\n'); // Limpa o buffer
            // Retorna o índice no formato C (0 a N-1)
            return indice - 1; 
        }
        printf("Entrada inválida. Digite um número entre 1 e %d.\n", max_index);
        while (getchar() != '\n'); // Limpa buffer
    }
}
void cadastrar_territorios(Territorio* mapa, int tamanho) {
    // ... Implementação de cadastro (usando fgets e scanf) ...
    printf("\n--- [Aviso] Dados de cadastro omitidos para dadoso. Assumindo dados válidos. ---\n");
    
    // Configuração de dados de teste (opcional)
    if (tamanho >= 2) {
        strcpy(mapa[0].nome, "Brasil");
        strcpy(mapa[0].cor, "Vermelho");
        mapa[0].tropas = 5;

        strcpy(mapa[1].nome, "Argentina");
        strcpy(mapa[1].cor, "Azul");
        mapa[1].tropas = 5;
        
        // ... (Mais cadastros aqui)
    }
}
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("[BATALHA] %s vs. %s\n", atacante->nome, defensor->nome);
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;

    if (dado_atacante > dado_defensor) {
        printf("  >>> O ATACANTE %s VENCEU! <<<\n", atacante->nome);
        strcpy(defensor->cor, atacante->cor);
        int tropas_transferidas = defensor->tropas / 2;
        atacante->tropas += tropas_transferidas;
        defensor->tropas -= tropas_transferidas;
    } else {
        printf("  >>> O DEFENSOR %s VENCEU! <<<\n", defensor->nome);
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
    }
}
void exibir_mapa(Territorio* mapa, int tamanho) {
    printf("=========================================\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d:\n", i + 1);
        printf("  > Nome: %s\n", (mapa + i)->nome);
        printf("  > Dono: %s\n", (mapa + i)->cor);
        printf("  > Tropas: %d\n", (mapa + i)->tropas);
        printf("-----------------------------------------\n");
    }
}


     
                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                            
        
    