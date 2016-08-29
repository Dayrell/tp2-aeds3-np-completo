//
//  funcoesGrafo.c
//  TP2
//
//  Created by Fábio Dayrell Rosa on 26/03/14.
//  Copyright (c) 2014 Dayrell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesGrafo.h"

// inicia a matriz que representa o grafo com 0 em todas as posições
void inicializaGrafo(tipoGrafo *grafo)
{
    int i, j;
    
    for(i = 0; i < grafo->numAlunos; i++)
    {
        for(j = 0; j < grafo->numRespostas; j++)
        {
            grafo->matriz[i][j] = 0;
        }
    }
}

// coloca '1' onde existir uma aresta no grafo
void preencheGrafo(FILE *arquivoEntrada, tipoGrafo *grafo)
{
    int numArestas, i = 0, vertice;
    char teste;
    
    numArestas = grafo->numRespostas;
    
    fscanf(arquivoEntrada, "%c", &teste);
    
    while(numArestas > 0)
    {
        // enquanto não chegar no final da linha
        do
        {
            fscanf(arquivoEntrada, "%d", &vertice);
            grafo->matriz[vertice-1][i] = 1;
        
            fscanf(arquivoEntrada, "%c", &teste);
    
        } while(((teste != '\n') && (teste != '\r')) && !(feof(arquivoEntrada)));

        numArestas--;
        i++;
    }
}