#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCESSO 1
#define FALHA 0

typedef struct tabela {
	char nome[50];
	int valor;
	struct tabela* prox;
} Tabela;

typedef struct codigo{
	unsigned int byte;
	unsigned int info;
	short int relocado;
	struct codigo *prox;
} Codigo;

typedef struct relocacao{
	unsigned int byte;
	struct relocacao *prox;
} Relocacao;


void liga(FILE*,FILE*,FILE*,char*);
Tabela* InsereTabela (Tabela*, char[], int);
Codigo* InsereCodigo (Codigo*, int, int);
Relocacao* InsereRelocacao (Relocacao*, int);
Tabela* CriaUso (Tabela*, FILE*);
Tabela* CriaDefinicoes (Tabela*, FILE*);
Codigo* CriaCodigo (Codigo*, FILE*);
Relocacao* CriaRelocacao (Relocacao*, FILE*);
int tamanho (Codigo*);
int EstaNa (char[],Tabela*);
int AnalisaIndefinicoes(Tabela*,Tabela*,Tabela*,Tabela*,Tabela*,Tabela*);
int AnalisaRedefinicoes(Tabela*,Tabela*,Tabela*);
Tabela* CriaGlobal (Tabela*,Tabela*,Tabela*,Tabela*);
void ImprimirCoidgo(Codigo*,Codigo*,Codigo*, FILE*);
Codigo* ResolveConflitosCruzados(Codigo*,Tabela*, Tabela*);
Codigo* RealocaRelativos(Codigo*, Relocacao*, int);
void copia (FILE*, char*);