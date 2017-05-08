#include"bibliotecas_montador.h"

void * CriaTabela(){
    return NULL;
}

TabelaDeSimbolos* InsereSimbolo (TabelaDeSimbolos* tabela, char nome[], int valor){
    TabelaDeSimbolos * novo = (TabelaDeSimbolos*) calloc(1,sizeof(TabelaDeSimbolos));
    strcpy(novo->nome, nome);
    novo->valor = valor;
    novo->prox = tabela;
    tabela = novo;
    return novo;
}
TabelaDeSimbolos* existe_simbolo(TabelaDeSimbolos* tabela,char* simb){
    while(tabela!=NULL){
        if(strcmp(tabela->nome,simb)==0){//achou simbolo na tabela de simbolos
            return tabela;
        }
        tabela = tabela->prox;
    }
    return NULL;
}
TabelaDeInstrucoes* inicializa_instrucoes(){
    TabelaDeInstrucoes* Tabela=InsereInstrucao(NULL,"add",1,2);
    Tabela = InsereInstrucao(Tabela,"sub",2,2);
    Tabela = InsereInstrucao(Tabela,"mult",3,2);
    Tabela = InsereInstrucao(Tabela,"div",4,2);
    Tabela = InsereInstrucao(Tabela,"jmp",5,2);
    Tabela = InsereInstrucao(Tabela,"jmpn",6,2);
    Tabela = InsereInstrucao(Tabela,"jmpp",7,2);
    Tabela = InsereInstrucao(Tabela,"jmpz",8,2);
    Tabela = InsereInstrucao(Tabela,"copy",9,3);
    Tabela = InsereInstrucao(Tabela,"load",10,2);
    Tabela = InsereInstrucao(Tabela,"store",11,2);
    Tabela = InsereInstrucao(Tabela,"input",12,2);
    Tabela = InsereInstrucao(Tabela,"output",13,2);
    Tabela = InsereInstrucao(Tabela,"stop",14,1);
    return Tabela;
}
TabelaDeInstrucoes* InsereInstrucao(TabelaDeInstrucoes* tabela,char*nome,short int opcode,short int tamanho){
    TabelaDeInstrucoes* novo = (TabelaDeInstrucoes*) malloc(sizeof(TabelaDeInstrucoes));
    if(novo==NULL){
        printf("Sistema Operacional nao conseguiu reservar espaco de memoria\n");
        exit(-1);
    }else{
        strcpy(novo->mnemonico, nome);
        novo->opcode = opcode;
        novo->tamanho = tamanho;
        novo->prox = tabela;
    }

    return novo;
}
TabelaDeInstrucoes* busca_instrucao(TabelaDeInstrucoes* tabela_instrucoes,char* tok){
    while(tabela_instrucoes!=NULL){
        if(strcmp(tabela_instrucoes->mnemonico,tok)==0){
            return tabela_instrucoes;
        }
        tabela_instrucoes = tabela_instrucoes->prox;
    }
    return NULL;
}
void libera_tabela_instrucoes(TabelaDeInstrucoes* ins){
    TabelaDeInstrucoes* aux;
    while(ins!=NULL){
        aux = ins->prox;
        free(ins);
        ins = aux;
    }
}
void libera_tabela_simbolos(TabelaDeSimbolos* s){
    TabelaDeSimbolos* aux;
    while(s!=NULL){
        aux = s->prox;
        free(s);
        s = aux;
    }
}
