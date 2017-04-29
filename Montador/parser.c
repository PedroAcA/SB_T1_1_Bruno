#include"bibliotecas_montador.h"
//#define FALSE 0
//#define TRUE !(FALSE)
void verifica_linhas(FILE* arq){
    int contador_posicao=0,contador_linha=1;
    int continua_busca_token;
    char *linha,*token;
    while(!feof(arq)){
        linha = proxima_linha(arq);
        printf("\nContador linha: %d\n",contador_linha);
        token = divide_tokens(linha);
        continua_busca_token = classifica(token,contador_linha,&contador_posicao);
        printf("\nContador posicao: %d\n",contador_posicao);
        while(token!=NULL && continua_busca_token){
            token = prox_token();
            continua_busca_token =classifica(token,contador_linha,&contador_posicao);
            printf("\nContador posicao: %d\n",contador_posicao);
        }
        contador_linha++;
        free(linha);
    }
}
/*classifica retorna se achou rotulos (TRUE) ou diretivas/instrucoes (FALSE)
Essas informacoes vao definir se eh necessario continuar avaliando os tokens
da linha ou se ja chegou no campo de operandos*/
int classifica(char* tok,int contador_linha, int* contador_posicao){
    if(existe_token(tok)){
        if(existe_rotulo(tok,contador_linha)){
            /*if(!existe_em_TS(tok){
                insere_rotulo_posicao(TS,*contador_posicao)
            }else{
                printf("Simbolo %s redefinido em %d",tok,contador_linha);
            }
            */
            printf("%s eh rotulo!\n",tok);
            return TRUE;
        }else if(!existe_instrucao(tok,contador_posicao)){
            if(!existe_diretiva(tok,contador_posicao)){
                printf("Operacao %s nao identificada na linha %d",tok,contador_linha);
            }
        }
    }
    return FALSE;
}
int existe_token(char* tok){
    return tok != NULL;
}
int existe_rotulo(char * tok, int contador_linha){
    int ultimo_caract = tam_string(tok)-2;
    if(tok[ultimo_caract] == ':'){// ultimo caracter valido do token eh : e primeiro nao eh numero sao os requisitos
        if(!eh_numero(tok[0])){
            return TRUE;
        }else{
            printf("%s mal formado em %d (rotulo nao pode comecar com numero)\n",tok,contador_linha);
        }
    }
    return FALSE;
}
int eh_numero(char c){
    return (c>='0' && c<='9');
}
int existe_instrucao(char *tok,int* contador_posicao){
    if(strcmp(tok,"add")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"sub")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"mult")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"div")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"jmp")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"jmpn")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"jmpp")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"jmpz")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"copy")==0){
            *contador_posicao = *contador_posicao + 3;
            return TRUE;
    }else if(strcmp(tok,"load")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"store")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"input")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"output")==0){
            *contador_posicao = *contador_posicao + 2;
            return TRUE;
    }else if(strcmp(tok,"stop")==0){
            *contador_posicao = *contador_posicao + 1;
            return TRUE;
    }
    return FALSE;
}
int existe_diretiva(char *tok,int *contador_posicao){
    return TRUE;
}
