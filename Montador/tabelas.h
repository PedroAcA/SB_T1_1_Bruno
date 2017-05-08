typedef struct simbolos{
    char nome[50];
    int valor;
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
/*
typedef struct diretivas{
    char nome[10];
    short int tamanho;
    struct diretivas *prox;
} TabelaDeDiretivas;
*/
// a TabeladeDiretivas vai facilitar a valiacao de divisoes por 0, modificacoes
// de constantes e acesso de espacos nao reservados de memoria
typedef struct diretivas{
    short int posicao_memoria;
    short int eh_cte;// para a diretiva const
    short int eh_zero;// para a diretiva const
    short int espacos_reservados;//para a diretiva space;
    struct diretivas *prox;
} TabelaDeDiretivas;

void* CriaTabela (void);
TabelaDeSimbolos* InsereSimbolo (TabelaDeSimbolos*, char*, int);
TabelaEQU* InsereEquivalencia (TabelaEQU*, char*);
TabelaDeSimbolos* existe_simbolo(TabelaDeSimbolos*,char*);
TabelaDeInstrucoes* inicializa_instrucoes(void);
TabelaDeInstrucoes* InsereInstrucao(TabelaDeInstrucoes*,char*,short int,short int);
TabelaDeInstrucoes* busca_instrucao(TabelaDeInstrucoes*,char*);
void libera_tabela_instrucoes(TabelaDeInstrucoes*);
void libera_tabela_simbolos(TabelaDeSimbolos*);

