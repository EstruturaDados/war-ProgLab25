#include <stdio.h>  // Entrada/Saída
#include <string.h> // Manipulação de strings

//--- Definição da estrutura 'Território' ---
typedef struct {
    char nome[50]; // Nome do território
    char cor_exercito[20]; // Cor do exército dominante
    int num_tropas;  // Número de tropas presentes
} Territorio;

int main(){
 //--- Declaração de vetor de structs ---
Territorio mapa[5]; // Mapa com 5 territórios
const int NUM_TERRITORIOS = 5;

//---Entrada de dados: Cadrastro dos 5 Territórios--- 
for(int i = 0; i < NUM_TERRITORIOS; i++){
    printf("\n --- Cadastro de Território %d de %d ---\n", i + 1, NUM_TERRITORIOS);
    //Entrada do nome do território (string)
    printf("Digite o nome do Território: ");
    fgets(mapa[i].nome, sizeof(mapa[i]).nome, stdin);

    //Remover o caractere de nova linha '\n' adicionado por fgets
    mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

    //Entrada da cor do exército dominante (string)
    printf("Digite a cor do Exército dominante: ");
    fgets(mapa[i].cor_exercito, sizeof(mapa[i]).cor_exercito, stdin);
    mapa[i].cor_exercito[strcspn(mapa[i].cor_exercito, "\n")] = '\0';

    //Entrada do número de tropas (inteiro)
    printf("Digite o número de tropas presentes: ");
    scanf("%d", &mapa[i].num_tropas);

    //Limpar o buffer do teclado para a próxima iteração
    while(getchar() != '\n');

}
 //--- Exibição dos dados cadastrados ---
    printf("\n================================================");
    printf("\n## ESTADO INICIAL DOS TERRITÓRIOS CADASTRADOS ##\n");
    printf("==================================================\n");

    for (int i = 0; i < NUM_TERRITORIOS; i++){
        printf("Território %d:\n", i + 1);
        // Acessar os campos usando o operador '.'
        printf("  >  Nome: %s\n", mapa[i].nome);
        printf("  >  Cor: %s\n", mapa[i].cor_exercito);
        printf("  >  Tropas: %d\n", mapa[i].num_tropas);
        printf("----------------------------------------------\n");
    }

    return 0;
}