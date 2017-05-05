#include"bibliotecas_montador.h"
void remove_desnecessarios (FILE * arq){
    FILE *pre = fopen("temp.pre","w") ;
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
     char* retorno_fgets;
       arq = fopen(nome_arq,"r");
    if(existe_arquivo(arq)){
        remove_desnecessarios(arq);
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!",nome_arq,198);
    }

    arq = fopen("temp.pre","r");

    TabelaEQU * tabela = NULL;

    if(existe_arquivo(arq)){
        while(!feof(arq)){
       retorno_fgets= fgets(linha,100,arq);
       // printf("linha lida: %s",linha);

        if(strcmp(linha,"section text\n") ==0)
            break;

        if (EhEQU(linha, token)  == 1){
            tabela = InsereEquivalencia(tabela,token);
        }
        limpa(linha,100);
        limpa(token,50);
    }

    }else{
        printf("Arquivo %s n%co encontrado!","temp.pre",198);
    }

    if(feof(arq))
        printf("SECTION TEXT FALTANTE\n");
    //printf("lista de equivalencias\n");
    //TabelaEQU * p;
    //for (p=tabela;p!=NULL; p= p->prox){
    //    printf("Nome: %s\n", p->nome);
    //}
    rewind(arq);

    resolve_equivalencias(arq, tabela);

    fclose(arq);

    remove("temp.pre");

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

int TaNaLista(char linha[], TabelaEQU* lista){
    int i;
    char token[50];
    TabelaEQU* p = lista;

    for(i=3;linha[i]!='\n';i++){
        token[i-3] = linha[i];
    }
    token[i-3] = '\0';

    while( (p!= NULL) && (strcmp(p->nome,token) != 0)){
        p= p->prox;
    }

    if(p==NULL)
        return 0;
    else
        return 1;
}

void resolve_equivalencias(FILE* arq, TabelaEQU* lista){
    FILE* arq2 = fopen("teste1.pre","w");
    char linha[100],token[50];
    char* retorno_fgets; // usado para remover os warnings e lidar com possiveis
                        // erros gerados pela fgets, caso necessario
    while(!feof(arq)){
        retorno_fgets=fgets(linha,100,arq);
       // printf("linha lida: %s",linha);

        if (EhEQU(linha,token) != 0){
            fprintf(arq2,"\n");
        }
        else if (linha[0] == 'i' && linha [1] == 'f'){
            if(TaNaLista(linha,lista)){
               fprintf(arq2,"\n");
               retorno_fgets= fgets(linha,100,arq);
                fprintf(arq2,"%s",linha);
            }
            else{
                fprintf(arq2,"\n");
               retorno_fgets= fgets(linha,100,arq);
                fprintf(arq2,"\n");
            }
        }
        else
            fprintf(arq2,"%s",linha);

        limpa(linha,100);
        limpa(token,50);

    }

    fclose(arq2);
}

