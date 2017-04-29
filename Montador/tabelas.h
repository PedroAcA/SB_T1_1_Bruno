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
TabelaEQU* InsereEquivalencia (TabelaEQU*, char*);
