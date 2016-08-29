//
//  funcoesGrafo.h
//  TP2
//
//  Created by Fábio Dayrell Rosa on 26/03/14.
//  Copyright (c) 2014 Dayrell. All rights reserved.
//

#ifndef TP2_funcoesGrafo_h
#define TP2_funcoesGrafo_h

typedef struct
{
    int **matriz;
    int numAlunos, numRespostas;
} tipoGrafo;

void inicializaGrafo(tipoGrafo *grafo);

void preencheGrafo(FILE *arquivoEntrada, tipoGrafo *grafo);

#endif
