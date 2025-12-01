#include <stdio.h>  // Entrada/Saída fegts, printf, scanf
#include <stdlib.h> // calloc,free, rand, srand
#include <time.h>   // time (para semente aleatória)
#include <string.h> // Manipulação de strings

//---DEFINIÇÃO DE STRUCT ATUALIZADA--- 
    typedef struct{
    char nome[30];
    char cor[10];
    int tropas;
 }Territorio;

//---PROTÓTIPOS DE FUNÇÕES---
Territorio* alocacar_mapa(int tamanho);
void cadastrar_territorios(Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
void exibir_mapa(Territorio* mapa, int tamanho);
void liberar_mapa(Territorio* mapa);

//=============================================================
//---FUNÇÃO PRINCIPAL---
//=============================================================
int main(){
    // REQUISITO:Utilizar srand(time (NUll)) e rand para garar números aleatórios
    srand(time(NULL)); // Semente para números aleatórios

    int num_territorios;
    Territorio* mapa = NULL;

    //CONFIGURAÇÃO INICIAL E ALOCAÇÃO DINÂMICA
    printf("--- 1 . CONFIGURAÇÃO (SETUP) ---\n");
    printf("Digite o número de territórios para o mapa: ");
    if (scanf("%d", &num_territorios) != 1 || num_territorios <= 0) {
        printf("Número de territórios inválido. Encerrando.\n");
        return 1;
    }
    while(getchar() != '\n'); // Limpar buffer do teclado

    mapa = alocacar_mapa(num_territorios);

    if(mapa == NULL) return 1; // Falha na alocação

    //CADASTRO DOS DADOS
    cadastrar_territorios(mapa, num_territorios);

    //SIMULAÇÃO DE ATAQUES (Exemplo: Território 0 ataca Território 1)
    printf("\n--- 2. ESTADO INICIAL DO MAPA ---\n");
    exibir_mapa(mapa, num_territorios);

    if(num_territorios >= 2){
        printf("\n--- 2.1 SIMULAÇÃO DE ATAQUE  (GAME LOGIC)---\n");
      // Passa o endereço dos Territórios que serão o atacante e o defensor
        atacar(&mapa[0], &mapa[1]);
    }else{
        printf("\n São necessários pelo menos 2 territórios para simular um ataque de teste.\n");
    }
    // 4. EXIBIÇÃO PÓS-ATAQUE
    printf("\n--- ESTADO DO APÓS O ATAQUE ---\n");
    exibir_mapa(mapa, num_territorios);

    //LIMPEZA (CLEANUP)
    liberarMemoria(mapa);

    return 0;
}
