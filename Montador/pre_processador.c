#include"bibliotecas_montador.h"
void remove_desnecessarios (FILE * arq){
    FILE *pre = fopen("teste1.pre","w") ;
    char c, anterior = 'a';

    while((c = fgetc(arq)) != EOF){
        if (c!= ';'){
            if(c != ' ' || anterior != ' '){
                c = tolower(c);
                fprintf(pre,"%c",c);
            }
        }
        else{
            while (fgetc(arq) != '\n' );
            fprintf(pre,"\n");
        }
        anterior = c;
    }
    fclose(pre);
}
void pre_processa(char *nome_arq){
     char linha[150], token[50];
     FILE* arq;
       arq = fopen(nome_arq,"r");
    if(existe_arquivo(arq)){
        remove_desnecessarios(arq);
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!",nome_arq,198);
    }

    arq = fopen("teste1.pre","r");

    TabelaEQU * tabela = NULL;

    if(existe_arquivo(arq)){
        while(!feof(arq)){
        fgets(linha,100,arq);
        printf("linha lida: %s",linha);

        if(strcmp(linha,"section text\n") ==0)
            break;

        if (EhEQU(linha, token)){
            tabela = InsereEquivalencia(tabela,token);
        }
        limpa(linha,100);
        limpa(token,50);
    }
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!","teste1.pre",198);
    }

    printf("lista de equivalencias\n");
    TabelaEQU * p;
    for (p=tabela;p!=NULL; p= p->prox){
        printf("Nome: %s\n", p->nome);
    }


}

int EhEQU (char *linha, char token[]){
    int i = 0;

    while (linha[i] != ' ')
        i++;

    if (linha[i-1] == ':' && linha[i+1] == 'e' && linha[i+2] == 'q' && linha[i+3] == 'u' && linha[i+5] == '1'){
        linha[i-1] = '\0';
        strcpy(token,linha);
        return 1;
    }
    else
        return 0;
}

void limpa(char* linha, int n){
    int i;
    for (i=0;i<n;i++){
        linha[i] = '\0';
    }
}

TabelaEQU* InsereEquivalencia (TabelaEQU* tabela, char nome[] ){
    TabelaEQU * novo = (TabelaEQU*) malloc(sizeof(TabelaEQU));
    strcpy(novo->nome, nome);
    novo->prox = tabela;
    tabela = novo;
    return tabela;
}

