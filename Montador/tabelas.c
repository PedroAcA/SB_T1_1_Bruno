#include"bibliotecas_montador.h"
//TabelaDeObjetos *Inicio=NULL,*Fim=NULL;// ponteiros internos para criar a fila de codigo objeto
                             // assim, é possivel escrever as tabelas e o codigo
                             // objeto na ordem em que aparecem
void * CriaTabela(){
    return NULL;
}
//a funcao InsereSimbolo insere simbolos nao Externos.
// Para inserir simbolos externos a funcao InsereSimbolo_Externo foi criada
TabelaDeSimbolos* InsereSimbolo (TabelaDeSimbolos* tabela, char nome[],short int valor){
    TabelaDeSimbolos * novo = (TabelaDeSimbolos*) calloc(1,sizeof(TabelaDeSimbolos));
    strcpy(novo->nome, nome);
    novo->valor = valor;
    novo->prox = tabela;
    novo->externo = 'n';
    tabela = novo;
    return novo;
}
TabelaDeSimbolos* busca_simbolo(TabelaDeSimbolos* tabela,char* simb){
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
/*A funcao busca_incrementa_posicao busca se a instrucao eh valida e, se for,
  atualiza o contador_posicao. Retorna TRUE(definido em pre_processador.h)
  se instrucao for valida ou FALSE (definido em pre_processador.h) caso
  contrario*/
TabelaDeInstrucoes* busca_incrementa_posicao(char*tok){
    // a funcao busca_instrucao esta definida em tabelas.c
    // a tabela de instrucoes esta declarada em bibliotecas_montador.h
    TabelaDeInstrucoes* buscador = busca_instrucao(Instrucoes,tok);// endereco de onde esta a instrucao na tabela de instrucoes (se esta existir)
    if(buscador!=NULL){
        contador_posicao+= buscador->tamanho;
    }
    return buscador;
}

TabelaDeDiretivas* insereDiretiva(TabelaDeDiretivas* Dir,int posicao_memoria,char tipo,int valor){
    TabelaDeDiretivas* novo = (TabelaDeDiretivas*)malloc(sizeof(TabelaDeDiretivas));
    if(novo==NULL){
        printf("Sistema Operacional nao conseguiu reservar espaco de memoria\n");
        exit(-1);
    }else{
        novo->posicao_memoria = posicao_memoria;
        novo->tipo = tipo;
        novo->valor= valor;
        novo->prox = Dir;
    }
    return novo;
}
TabelaDeDiretivas* busca_end_incial(TabelaDeDiretivas* Diretivas, int end_base){
    while(Diretivas!=NULL){
        if(Diretivas->posicao_memoria == end_base){
            return Diretivas;
        }
        Diretivas = Diretivas->prox;
    }
    return Diretivas;
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
void libera_tabela_diretivas(TabelaDeDiretivas* d){
    TabelaDeDiretivas* aux;
    while(d!=NULL){
        aux = d->prox;
        free(d);
        d = aux;
    }
}
/*
void Insere_Codigo_Objeto_Instr(TabelaDeInstrucoes* instrucao,short int* args){
    TabelaDeObjetos* novo = (TabelaDeObjetos*)malloc(sizeof(TabelaDeObjetos));
    if(novo!=NULL){
        novo->tipo = 'I';
        novo->prox=NULL;
        novo->valor = instrucao->opcode;
        if(strcmp(instrucao->mnemonico,"copy")==0){
            novo->op1 = args[0];
            novo->op2 = args[1];
        }else if(strcmp(instrucao->mnemonico,"stop")!=0){// instrucao a ser salva nao eh stop
            novo->op1 = args[0];
        }
        if(Inicio==NULL){
            Inicio = novo;
            Fim = novo;
        }else{
            Fim->prox = novo;
            Fim = novo;
        }
    }else{
        printf("Sistema Operacional nao conseguiu reservar espaco de memoria\n");
        exit(-1);
    }
}

void Insere_Codigo_Objeto_Dir(char tipo,short int valor){
    TabelaDeObjetos* novo = (TabelaDeObjetos*)malloc(sizeof(TabelaDeObjetos));
    if(novo!=NULL){
        novo->tipo = tipo;
        novo->prox=NULL;
        novo->valor = valor;
        if(Inicio==NULL){
            Inicio = novo;
            Fim = novo;
        }else{
            Fim->prox = novo;
            Fim = novo;
        }
    }else{
        printf("Sistema Operacional nao conseguiu reservar espaco de memoria\n");
        exit(-1);
    }
}
void desaloca_Tabela_Objetos(){
    TabelaDeObjetos* aux
    while(Inicio!=NULL){
        aux = Inicio->prox;
        free(Inicio);
        Inicio=aux;
    }
}
*/
