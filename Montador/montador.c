#include"bibliotecas_montador.h"
int main(){
    char* nome_arq ={"teste1.asm"};
    FILE* arq;
    TabelaDeSimbolos* TS = CriaTabela();
//  char *linha,*token;
    passagem = 0;
    pre_processa(nome_arq);
    passagem++;
    arq = fopen("teste1.pre","r");
    if(existe_arquivo(arq)){
        verifica_linhas(arq,&TS);
    }else{
        //\u00E3 eh ã para unicode. 198 eh ã em ASCII
        printf("Arquivo %s n\u00E3o encontrado!","teste1.pre");
    }
  /*  if(existe_arquivo(arq)){
        while(!feof(arq)){
            linha = proxima_linha(arq);
            printf("Linha lida:\n\t%s \n",linha);
            token = divide_tokens(linha);
            printf("Tokens:\n");
            while(token!=NULL){
                printf("\t%s \n",token);
                token = prox_token();
            }
            free(linha);
        }
        fclose(arq);
    }else{
        printf("Arquivo %s n%co encontrado!","teste1.pre",198);
    }*/
    return 0;
}
