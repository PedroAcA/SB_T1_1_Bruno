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
     char *linha, *token, equ[50];
     FILE* arq;
       arq = fopen(nome_arq,"r");
    if(existe_arquivo(arq)){
        preprocessamento(arq);
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!",nome_arq,198);
    }

    arq = fopen("teste1.pre","r");

    TabelaEQU * equivalencias;

    if(existe_arquivo(arq)){
        while(!feof(arq)){
            linha = proxima_linha(arq);

            printf("Linha lida:\n\t%s \n",linha);
            if (strcmp(linha, "section text") == 0 )
                break;;
            token = divide_tokens(linha);

            if (token[sizeof(token)-1] == ':'){
                strcpy(equ, token);
            }

            while(token!=NULL){
                //printf("\t%s \n",token);
                token = prox_token();
            }
            free(linha);
        }
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!","teste1.pre",198);
    }
}
