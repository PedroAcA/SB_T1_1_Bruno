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
int passagem;
TabelaDeInstrucoes* Instrucoes;
