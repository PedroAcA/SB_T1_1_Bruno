/* container de todas as bibliotecas usadas pelo montador
   para, por exemplo, fazer #include"bibliotecas_montador.h" em
   todos os .c em vez de 2 ou mais includes (stdio, stdlib e string, etc)*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"scanner.h"
#include"arquivos.h"
#include"pre_processador.h"
#include"tabelas.h"
#include"parser.h"
#include "parser2.h"
short int *indice_realocacao;
int contador_linha,rotulos_linha,tamanho_realoc;
short int contador_posicao;
int passagem,total_erros,fechou_begin_end,endereco_dados;
TabelaDeInstrucoes* Instrucoes;
TabelaDeSimbolos* TS;
TabelaDeDiretivas* Tab_Dir;
