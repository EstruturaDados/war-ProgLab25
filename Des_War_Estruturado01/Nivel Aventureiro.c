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

//---PROTOTIPOS DE FUNÇÕES---
Territorio* alocacar_mapa(int tamanho);
void cadastrar_territorios(Territorio* mapa, int tamanho);

