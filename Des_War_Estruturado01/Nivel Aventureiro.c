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

//=============================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
//=============================================================

// REQUISITO: Usar calloc /malloc para alocação dinâmica.
Territorio* alocacar_mapa(int tamanho){
    //Usar para alocar mémoria e inicializar todos os campos com 0.
    Territorio* novo_mapa = (Territorio*) calloc(tamanho, sizeof(Territorio));

    if (novo_mapa == NULL){
        printf("ERRO FATAL: Falha na locação de mémoria (calloc).\n");
        return NULL;
    }
    printf("Mémoria alocada dinamicamente para %d territórios.\n", tamanho);
    return novo_mapa;
}

// REQUISITOS: Implementação das rotinas de cadastro.
void cadastrar_territorios(Territorio* mapa, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("\n --- Cadastro do Território %d de %d ---\n", i + 1, tamanho);

    // Entrada do Nome: '->' para ponteiros
    printf("Nome do Território: ");
    fgets((mapa + i)->nome, sizeof((mapa + i)->nome), stdin);
    (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = '\0'; 

    // Entrada da Cor
    printf("Cor do Exército dominante: ");
    fgets((mapa + i)->cor, sizeof((mapa + i)->cor), stdin);
    (mapa + i)->cor[strcspn((mapa + i)->cor, "\n")] = '\0';

    // Entrada do Número de Tropas
    printf("Número de Tropas presentes: ");
    // O  & antes do campo das 'tropas' 
    scanf("%d", &((mapa + i)->tropas));

    while(getchar() != '\n'); // Limpar buffer do teclado
    }

}
// REQUISITO: Implementação da lógica de ataque.
void atacar(Territorio* atacante, Territorio* defensor){
    printf("[BATALHA] %s (%s) vs %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Tropas: Atacante %d | Defensor %d\n", atacante->tropas, defensor->tropas);

    // Simulação do dado (Número aleatório entre 1 e 6)
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;

    printf("Dados: Atacante %d | Defensor %d\n", dado_atacante, dado_defensor);
    //Lógica de vitória (Atacante vence)
    if(dado_atacante > dado_defensor){
        printf(">>> O ATACANTE %s VENCEU! <<<\n", atacante->nome);

    // REQUISITO: Transfere a cor (defensor muda de dono).
        strcpy(defensor->cor, atacante->cor);

    // REQUISITOS: Transfere metade das tropas do defensor para o atacante.
       int tropas_transferidas = defensor->tropas / 2;
       atacante->tropas += tropas_transferidas;
       defensor->tropas -= tropas_transferidas; 

       printf(" -> %d tropas transferidas . Novo Dono: %s\n", tropas_transferidas, defensor->cor);
    }
    // Lógica de Derrota (Defensor vence)
    else {
        printf(" >>> O DEFENSOR %s VENCEU! <<<\n", defensor->nome);

        // REQUISITO: O atacante perde UMA tropa.
        if(atacante->tropas > 0){
           atacante->tropas -= 1;
           printf(" -> %s perdeu 1 tropa na falha do ataque.\n", atacante->nome);
    }
}
}
// Função utilitária para exibir o estado do mapa.
void exibir_mapa(Territorio* mapa, int tamanho){
   printf("================================================\n");
   for(int i = 0; i < tamanho; i++){
    printf("Território %d:\n", i + 1);
    // Acessar os campos usando '->' para ponteiros
    printf("  >  Nome: %s\n", (mapa + i)->nome);
    printf("  >  Cor: %s\n", (mapa + i)->cor);
    printf("  >  Tropas: %d\n", (mapa + i)->tropas);
    printf("----------------------------------------------\n");
   }
}
// REQUISITO: Função void liberarMemoria (Território* mapa) para liberar o espaço alocado.
void liberarMemoria(Territorio* mapa){
    if (mapa !=NULL){
        free(mapa);
        printf("Mémoria liberada com sucesso.\n");
    }
}