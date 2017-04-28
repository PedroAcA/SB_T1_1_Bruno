#include"bibliotecas_montador.h"

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
