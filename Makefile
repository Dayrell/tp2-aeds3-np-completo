######################################################################
# Desenvolvido por: Bruno Maciel Peres - brunomperes@dcc.ufmg.br
# www.homepages.dcc.ufmg.br/~brunomperes/
#
# Adaptado por Lidía Silva Ferreira 
# Matricula: 2010054622
#
# Readaptação por Édipo Fernandes Vieira de Oliveira
# Matricula: 2011054324
#
# Readaptação++ por Fábio Dayrell F. M. Rosa
# Matrícula: 2011054383
#
# Matéria: AEDSIII 2013/1
# Trabalho: TP2
# UFMG - Departamento de Ciência da Computação
######################################################################
# Lista dos objetos (arquivos .c, troca-se a extensão para .o) necessários para o programa final
OBJS1 = mainH.o funcoesHeuristica.o funcoesGrafo.o
OBJS2 = mainE.o funcoesOtimo.o funcoesGrafo.o

# Nome do executável
MAIN1 = tp2h 
MAIN2 = tp2e

# Argumentos para execução do programa
ARGS1 = input.txt output.txt
ARGS2 = input.txt output.txt

# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -pg -g3

# Opções para execução do Valgrind
VALOPS = --leak-check=full --show-reachable=yes

# Compilação do programa e passos das ligações de dependências
all: $(MAIN1) $(MAIN2)

$(MAIN1): $(OBJS1)
	@echo ""
	@echo " --- COMPILANDO PROGRAMA 1 ---"
	@$(CC) $(CFLAGS) $(OBJS1) -lm -o $(MAIN1)
	@echo ""

$(MAIN2): $(OBJS2)
	@echo ""
	@echo " --- COMPILANDO PROGRAMA 2 ---"
	@$(CC) $(CFLAGS) $(OBJS2) -lm -o $(MAIN2)
	@echo ""

%.o: %.c %.h
	@echo ""
	@echo " --- COMPILANDO OBJETO \"$@\""
	@$(CC) $(CFLAGS) $< -c 

run-h: $(MAIN1)
	./$(MAIN1) $(ARGS1)
run-e: $(MAIN2)	
	./$(MAIN2) $(ARGS2)

valgrind: $(MAIN1)
	valgrind $(VALOPS) ./$(MAIN1) $(ARGS1)
	$(MAIN2)
	valgrind $(VALOPS) ./$(MAIN2) $(ARGS2)

gprof: $(MAIN1)
	./$(MAIN1) $(ARGS1)
	gprof -b -p $(MAIN1)
	$(MAIN2)
	./$(MAIN2) $(ARGS2)
	gprof -b -p $(MAIN2)



