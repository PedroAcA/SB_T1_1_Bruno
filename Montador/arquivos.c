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
void escreve_instrucao(TabelaDeInstrucoes *instrucao_atual,short int* args){
    if(obj!=NULL){
        if(strcmp(instrucao_atual->mnemonico,"copy")==0 ){
            fprintf(obj,"%d %d %d ",(int)instrucao_atual->opcode,(int)args[0],(int)args[1]);
        }else if(strcmp(instrucao_atual->mnemonico,"stop")==0){
            fprintf(obj,"%d ",(int)instrucao_atual->opcode);
        }else{
            fprintf(obj,"%d %d ",(int)instrucao_atual->opcode,(int)args[0]);
        }
    }
}
void escreve_diretiva(char tipo, short int valor){
    short int i;
    if(obj!=NULL){
        if(tipo == 'E'){
            for(i=0;i<valor;i++)
                fprintf(obj,"%d ",0);
        }else if(tipo== 'C'){
            fprintf(obj,"%d ",valor);
        }
    }
}
void escreve_tabelas(){
    escreve_tabela_uso();
    escreve_tabela_definicao();
    escreve_tabela_realoc();
}
void escreve_tabela_uso(){
    if(obj!=NULL){
        fprintf(obj,"\n\nTABLE USE\n");
        fprintf(obj,"\n");
    }
}
void escreve_tabela_definicao(){
    if(obj!=NULL){
        fprintf(obj,"TABLE DEFINITION\n");
        fprintf(obj,"\n");
    }
}
void escreve_tabela_realoc(){
    int i;
    if(obj!=NULL){
        fprintf(obj,"TABLE REALOCATION\n");
        for(i=0;i<(tamanho_realoc-1);i++)
            fprintf(obj,"%d ",(int)indice_realocacao[i]);

        fprintf(obj,"\n");
    }
}
