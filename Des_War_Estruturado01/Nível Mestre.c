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

// =================================================================
// Função Principal (MAIN): O LAÇO DO JOGO
// =================================================================
int 
    srand(time(NULL)); 
    
    int num_territorios;
    Territorio* mapa = NULL;
    int jogo_ativo = 1;

    // --- 1. CONFIGURAÇÃO INICIAL (SETUP) ---
    printf("--- CONFIGURAÇÃO INICIAL ---\n");
    printf("Digite o número total de territórios - mínimo 2: ");
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
     
     
     
                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                            
        
    