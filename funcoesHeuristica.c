//
//  funcoesHeuristica.c
//  TP2
//
//  Created by Fábio Dayrell Rosa on 30/03/14.
//  Copyright (c) 2014 Dayrell. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "funcoesGrafo.h"

/* Verifica se o aluno a ser adicionado já respondeu algo igual aos que foram
 * adicionados anteriormente. Caso tenha, esse aluno não é adicionado no 
 * conjunto */
int verificaEPreencheVetor(int aluno, int *vetorVerificador, tipoGrafo *grafo)
{
    int i;
    
    for(i = 0; i < grafo->numRespostas; i++)
    {
        /* se uma resposta dada pelo aluno já tiver sido marcada por outro 
         * aluno, o aluno que está sendo verificado não é adicionado no conjunto
         */
        if(vetorVerificador[i] == 1 && grafo->matriz[aluno][i] == 1)
            return 1;
    }
    
    /* caso contrário, o aluno é adicionado (as suas respostas são adicionadas
     * no vetor verificador */
    for(i = 0; i < grafo->numRespostas; i++)
    {
        vetorVerificador[i] = grafo->matriz[aluno][i] == 1;
    }
    
    return 0;
}

// escolhe o aluno que marcou menos respostas
int escolheMenor(int *quantidadeDeRespostasAluno, tipoGrafo *grafo)
{
    int menor, aluno = 0, i;
    
    menor = grafo->numRespostas+1;
    
    for(i = 0; i < grafo->numAlunos; i++)
    {
        if(quantidadeDeRespostasAluno[i] < menor &&
           quantidadeDeRespostasAluno[i] != -1)
        {
            menor = quantidadeDeRespostasAluno[i];
            aluno = i;
        }
    }
    
    /* troco a sua quantidade de respostas para -1 para ele não ser selecionado 
     * novamente */
    quantidadeDeRespostasAluno[aluno] = -1;
    
    return aluno;
}

// verifica quantas respostas cada aluno marcou
void verificaQuantidadeDeRespostas(int *quantidadeDeRespostasAluno,
                                   tipoGrafo *grafo)
{
    int i, j, numRespostas = 0;
    
    for(i = 0; i < grafo->numAlunos; i++)
    {
        for(j = 0; j < grafo->numRespostas; j++)
        {
            if(grafo->matriz[i][j] == 1)
                numRespostas++;
        }
        quantidadeDeRespostasAluno[i] = numRespostas;
        numRespostas = 0;
    }
        
}

void verificaConjunto(tipoGrafo *grafo, FILE *saida)
{
    int i, menor, flag = 0, tamConjunto = 0;
    
    int *quantidadeDeRespostasAluno, *vetorVerificador;
    quantidadeDeRespostasAluno = (int*)(malloc(sizeof(int*) *
                                               grafo->numAlunos));
    vetorVerificador = (int*)(malloc(sizeof(int*) * grafo->numRespostas));
    
    // inicializo o vetor verificador com 0 em todas as posições
    for(i = 0; i < grafo->numRespostas; i++)
        vetorVerificador[i] = 0;
    
    // verifico quantas respostas cada aluno marcou
    verificaQuantidadeDeRespostas(quantidadeDeRespostasAluno, grafo);
    
    i = 0;
    
    while(i < grafo->numAlunos)
    {
        /* escolhe o aluno com menos respostas (exceto aqueles que já foram 
         * escolhidos */
        menor = escolheMenor(quantidadeDeRespostasAluno, grafo);
        
        /* se retornar 0, é porque as respostas de mais um aluno foram 
         adicionadas no vetor verificador, então mais um aluno foi adicionado ao 
         * conjunto */
        flag = verificaEPreencheVetor(menor, vetorVerificador, grafo);
        
        if(flag == 0)
            tamConjunto++;
        
        i++;
        
    }
    fprintf(saida, "%d", tamConjunto);
    
}