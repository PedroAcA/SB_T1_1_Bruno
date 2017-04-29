#define TRUE 1
#define FALSE 0

typedef struct EQU{
    char nome[50];
    struct EQU* prox;
} TabelaEQU;

void preprocessamento (FILE * );
void pre_processa(char *);
int EhEQU (char *, char[]);
void limpa(char* , int);
void lista_equivalencias (FILE*, TabelaEQU*);
