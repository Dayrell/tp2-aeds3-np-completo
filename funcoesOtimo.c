//
//  funcoesOtimo.c
//  TP2
//
//  Created by Fábio Dayrell Rosa on 28/03/14.
//  Copyright (c) 2014 Dayrell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoesGrafo.h"

// coloca 0 em todas as posicoes do vetor
void reiniciaVetor(int *vetorConjunto, tipoGrafo *grafo)
{
    int i;
    
    for(i = 0; i < grafo->numRespostas; i++)
        vetorConjunto[i] = 0;
}

// retorna 1 se existem respostas repetidas
int preencheConjuntoVertices(int **grafo, int numRespostas, int numAluno,
                             int *vetorConjunto)
{
    int i;
    
    for(i = 0; i < numRespostas; i++)
    {
        if(grafo[numAluno][i] == 1 && vetorConjunto[i] != 1)
            vetorConjunto[i] = 1;
        else if(grafo[numAluno][i] == 1 && vetorConjunto[i] == 1)
        {
            return 1; //conjunto inválido
        }
    }
    
    return 0; // conjunto válido
}

void verificaConjunto(tipoGrafo *grafo, FILE *saida)
{
    int i, j, *conjuntoVertices, flag = 0, tamConjunto = 0, numVertices;
    
    unsigned int numConjuntos = pow(2, grafo->numAlunos);
    
    // O vetor conjuntoVertices permitirá ver qual é o conjunto máximo
    conjuntoVertices = (int*)(malloc(sizeof(int*) * grafo->numRespostas));
    
    reiniciaVetor(conjuntoVertices, grafo);
	
    // veritica todos os conjuntos de alunos possíveis
	for(i = 0; i < numConjuntos; i++)
    {
        numVertices = 0;
        for(j = 0; j < grafo->numAlunos; j++)
		{
            /* verifica se existem respostas repetidas em casa conjunto possível
             * de alunos */
			if(i & (1<<j))
			{
                numVertices++;
                flag = preencheConjuntoVertices(grafo->matriz,
                                                grafo->numRespostas, j,
                                                conjuntoVertices);
                
                if(flag == 1)
                    break;
			}
		}
        /* se não existir respostas repetidas no conjunto, verifico se esse
         * conjunto é maior do que o maior conjunto lido até o momento */
        if(flag == 0)
        {
            if(numVertices > tamConjunto)
                tamConjunto = numVertices;
        }
        
        reiniciaVetor(conjuntoVertices, grafo);
        
    }
    
    fprintf(saida, "%d", tamConjunto);
}