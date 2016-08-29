//
//  main.c
//  TP2
//
//  Created by Fábio Dayrell Rosa on 26/03/14.
//  Copyright (c) 2014 Dayrell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "funcoesOtimo.h"
#include "funcoesGrafo.h"

int main(int argc, const char * argv[])
{
    int numInstancias, i;
    
    // início da abertura de arquivos
    FILE *entrada = NULL, *saida = NULL;
    
    if(((entrada = fopen(argv[1], "r")) == NULL) ||
       ((saida = fopen(argv[2], "w")) == NULL))
    {
        printf("Erro ao abrir um dos arquivos!\n");
        
        return 0;
    }
    // fim da abertura de arquivos
    
    
    // lê o número de instâncias, vértices e arestas
    fscanf(entrada, "%d", &numInstancias);
    
    
    // aplica as funções abaixo a cada instância
    while(numInstancias > 0)
    {
        tipoGrafo grafo;
        
        // lê o número de vértices e arestas
        fscanf(entrada, "%d", &grafo.numAlunos);
        fscanf(entrada, "%d", &grafo.numRespostas);
        
        // início da alocação de memória para o grafo/matriz
        grafo.matriz = (int **) malloc(sizeof(int *) * grafo.numRespostas + 1);
        
        for(i = 0; i < grafo.numAlunos; i++)
            grafo.matriz[i] = (int *) malloc(sizeof(int) * grafo.numRespostas);
        // fim da alocação de memória para o grafo/matriz
        
        // cria um grafo representado por matriz com 0 em todas as posições
        inicializaGrafo(&grafo);
        
        preencheGrafo(entrada, &grafo);
        
        // Verifica todos os conjuntos possíveis a fim de encontrar o maior válido
        verificaConjunto(&grafo, saida);
        
        if(numInstancias > 1)
            fprintf(saida, "\n");
        
        numInstancias--;
    }
    
    
    fclose(entrada);
    fclose(saida);
    
    return 0;
}

