#include"bibliotecas_montador.h"
int main(){
    char* nome_arq ={"teste1.asm"};
    FILE* arq;
    char *linha,*token;
    pre_processa(nome_arq);
    arq = fopen("teste1.pre","r");
    if(existe_arquivo(arq)){
        while(!feof(arq)){
            linha = proxima_linha(arq);
            printf("Linha lida:\n\t%s\n",linha);
            token = divide_tokens(linha);
            printf("Tokens:\n");
            while(token!=NULL){
                printf("\t%s\n",token);
                token = prox_token();
            }
            free(linha);
        }
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!","teste1.pre",198);
    }
}
