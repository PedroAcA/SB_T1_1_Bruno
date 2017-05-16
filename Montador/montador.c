#include"bibliotecas_montador.h"
int main(int argc, char *argv[]){
    char* nome_arq ={"teste1.asm"};
    FILE *arq;
    //analisa_args_linha_comando(argc,argv);

    indice_realocacao = (short int*)malloc(sizeof(short int));
    indice_realocacao[0] = -1; //flag inicial para indicar que nao ha nada no inicio
    tamanho_realoc=1;
    TS =NULL;
    TD=NULL;
    TU=NULL;
    endereco_dados =-1;//indica onde comeca a secao de dados, se ela existe. Se nao existir, variavel tem valor -1
    fechou_begin_end = TRUE;
    tem_stop = FALSE;
    tem_begin = FALSE;
    total_erros = 0;
    Instrucoes = inicializa_instrucoes();
    Tab_Dir = NULL;
    passagem = 0;
    pre_processa(nome_arq);
    passagem++;
    arq = fopen("teste1.pre","r");
    if(existe_arquivo(arq)){
     //   printf("PASSAGEM:%d\n",passagem);
        verifica_linhas(arq);
        rewind(arq);
        transfere_da_TS_para_TabelaDefinicoes(TS,TD);
        passagem++;
    //    printf("PASSAGEM:%d\n",passagem);
        cria_arq_obj();
        verifica_linhas(arq);
        fclose(arq);
       // printf("\nEnderecoo dados: %d\n",endereco_dados);
    }else{
        //\u00E3 eh ã para unicode. 198 eh ã em ASCII
        printf("Arquivo %s n\u00E3o encontrado!","teste1.pre");
    }

    if(tem_begin){
        if(!fechou_begin_end){
            printf("\nArquivo eh modulo, mas nao fechou o begin..end\n");
            total_erros++;
        }
    }else if(!tem_stop){
        printf("\nArquivo nao eh modulo, mas nao tem stop\n");
        total_erros++;
    }
    if(total_erros>0){
        exclui_arq_obj();
    }else{
        if(tem_begin)
            escreve_tabelas();
        fecha_arq_obj();
    }
    printf("\nTotal de erros: %d\n",total_erros);
    libera_tabela_definicoes(TD);
    libera_tabela_uso(TU);
    libera_tabela_instrucoes(Instrucoes);
    libera_tabela_simbolos(TS);
    libera_tabela_diretivas(Tab_Dir);
    free(indice_realocacao);

    return 0;
}
