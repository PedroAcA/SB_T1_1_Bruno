#include"bibliotecas_montador.h"
int main(){
    char* nome_arq ={"teste1.asm"};
   // printf("oI\n");
    FILE* arq;
    TS =NULL;
    endereco_dados =-1;//indica onde comeca a secao de dados, se ela existe. Se nao existir, variavel tem valor -1
    fechou_begin_end = TRUE;
    total_erros = 0;
    Instrucoes = inicializa_instrucoes();
//  char *linha,*token;
    passagem = 0;
    pre_processa(nome_arq);
  //    printf("oI\n");
    passagem++;
    arq = fopen("teste1.pre","r");
    if(existe_arquivo(arq)){
        verifica_linhas(arq);
        rewind(arq);
        passagem++;
        verifica_linhas(arq);
        fclose(arq);

    }else{
        //\u00E3 eh ã para unicode. 198 eh ã em ASCII
        printf("Arquivo %s n\u00E3o encontrado!","teste1.pre");
    }

    printf("\nTotal de erros: %d\n",total_erros);
    libera_tabela_instrucoes(Instrucoes);
    libera_tabela_simbolos(TS);
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
