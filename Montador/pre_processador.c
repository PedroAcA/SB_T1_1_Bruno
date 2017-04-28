#include"bibliotecas_montador.h"
void preprocessamento (FILE * arq){
    FILE *pre = fopen("teste1.pre","w") ;
    char c;

    while((c = fgetc(arq)) != EOF){
        if (c!= ';'){
            c = tolower(c);
            fprintf(pre,"%c",c);
        }
        else{
            while (fgetc(arq) != '\n' );
            fprintf(pre,"\n");
        }
    }
    fclose(pre);
}
void pre_processa(char *nome_arq){
     FILE* arq;
       arq = fopen(nome_arq,"r");
    if(existe_arquivo(arq)){
        preprocessamento(arq);
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!",nome_arq,198);
    }
}
