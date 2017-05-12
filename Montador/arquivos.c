#include"bibliotecas_montador.h"
FILE *obj;
int existe_arquivo(FILE* arq){
    return arq!=NULL;
}
void cria_arq_obj(){
    obj = fopen("teste1.o","w+");
    if(obj!=NULL)
        fprintf(obj,"CODE\n");
}
void exclui_arq_obj(){
    if(obj!=NULL){
        remove("teste1.o");
    }
}
void escreve_instrucao(TabelaDeInstrucoes* instrucao_atual,short int* args){
    if(obj!=NULL){
        if(strcmp(instrucao_atual,"copy")==0 ){
            fprintf("%d %d %d",(int)instrucao_atual->opcode,(int)args[0],(int)args[1]);
        }else if(strcmp(instrucao_atual,"stop")==0){
            fprintf("%d ",(int)instrucao_atual->opcode);
        }else{
            fprintf("%d %d ",(int)instrucao_atual->opcode,(int)args[0]);
        }
    }
}
void escreve_tabela_definicao(){
    if(obj!=NULL){
        fprintf(obj,"TABLE DEFINITION\n");
    }
}
