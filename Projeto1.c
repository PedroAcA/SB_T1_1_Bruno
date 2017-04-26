#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct simbolos{
    char nome[50];
    int valor;
    struct simbolos *prox;
} TabelaDeSimbolos;

typedef struct instrucaoes{
    char mnemonico[4];
    short int opcode;
    short int tamanho;
    short int operandos;
    struct instrucaoes* prox;
} TabelaDeInstrucoes;

typedef struct diretivas{
    char nome[10];
    short int tamanho;
    struct diretivas *prox;
} TabelaDeDiretivas;

void* CriaTabela (void);
TabelaDeSimbolos* InsereSimbolo (TabelaDeSimbolos*, char*, int);


int main(){

    TabelaDeSimbolos *tabela1 = (TabelaDeSimbolos*) CriaTabela();
    TabelaDeInstrucoes *tabela2 = (TabelaDeInstrucoes*) CriaTabela();
    TabelaDeDiretivas *tabela3 = (TabelaDeDiretivas*) CriaTabela();



    return 0;
}

void * CriaTabela(){
    return NULL;
}

TabelaDeSimbolos* InsereSimbolo (TabelaDeSimbolos* tabela, char nome[], int valor){
    TabelaDeSimbolos * novo = (TabelaDeSimbolos*) malloc(sizeof(TabelaDeSimbolos));
    strcpy(novo->nome, nome);
    novo->valor = valor;
    novo->prox = tabela;
    tabela = novo;
    return tabela;
}

