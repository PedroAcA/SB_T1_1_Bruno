typedef struct simbolos{
    char nome[50];
    short int valor;
    struct simbolos *prox;
} TabelaDeSimbolos;

typedef struct instrucaoes{
    char mnemonico[7];//6 caracteres de output + '\0'
    short int opcode;
    short int tamanho;//numero total de blocos de 16 bits que os operandos + instrucao ocupa ocupam
                     // como o contador de posicao comeca em zero, somar o tamnho total gera o contador para a proxima instrucao
    short int operandos;// eh realmente necessario se ja tem tamanho?
    struct instrucaoes* prox;
} TabelaDeInstrucoes;

typedef struct obj{
    char tipo;// valores posssiveis sao 'C' (constante), 'E'(espaco) ou 'I'(instrucao)
    short int op1;
    short int op2;
    short int valor;// vai indicar valor da constante (para o caso , numero de espacos alocados ou opcode)
    struct obj *prox;
} TabelaDeObjetos;//salva todas as informacoes necessarias para fazer o codigo objeto

// a TabeladeDiretivas vai facilitar a valiacao de divisoes por 0, modificacoes
// de constantes e acesso de espacos nao reservados de memoria
typedef struct diretivas{
    short int posicao_memoria;//contador_posicao no momento em que const ou space foram chamadas
    char tipo;// valores posssiveis sao 'C' (constante), 'E'(espaco)
    short int valor;//para a diretiva space sao os espcaos reservado e para a const eh o numero reservado (a fim de saber se ha divisao por 0);
    struct diretivas *prox;
} TabelaDeDiretivas;

void* CriaTabela (void);
TabelaDeSimbolos* InsereSimbolo (TabelaDeSimbolos*, char*,short int);
TabelaDeSimbolos* existe_simbolo(TabelaDeSimbolos*,char*);
TabelaDeInstrucoes* inicializa_instrucoes(void);
TabelaDeInstrucoes* InsereInstrucao(TabelaDeInstrucoes*,char*,short int,short int);
TabelaDeInstrucoes* busca_instrucao(TabelaDeInstrucoes*,char*);
TabelaDeDiretivas* insereDiretiva(TabelaDeDiretivas*,int,char,int);
TabelaDeDiretivas* busca_end_incial(TabelaDeDiretivas*,int);
void libera_tabela_instrucoes(TabelaDeInstrucoes*);
void libera_tabela_simbolos(TabelaDeSimbolos*);
void libera_tabela_diretivas(TabelaDeDiretivas*);

