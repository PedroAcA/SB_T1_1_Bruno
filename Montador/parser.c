#include"bibliotecas_montador.h"
//#define FALSE 0
//#define TRUE !(FALSE)
/*a variavel rotulos_linha indica quantos rotulos existem por linha
(possibilita detectar o erro de mais de um rótulo por linha)
*/
int contador_posicao,contador_linha,rotulos_linha;

void verifica_linhas(FILE* arq,TabelaDeSimbolos** TS){
    int continua_busca_token;
    char *linha,*token;
    rotulos_linha = 0;
    contador_posicao=0;
    contador_linha=1;
    while(!feof(arq)){
        linha = proxima_linha(arq);
      //  printf("\nLinha lida %s\n",linha);
      //  printf("\nContador linha: %d\n",contador_linha);
        token = divide_tokens(linha);
        //printf("\nToken lido %s\n",token);
        continua_busca_token = classifica(token,TS);
      //  printf("\nContador posicao: %d\n",contador_posicao);
        while(token!=NULL && continua_busca_token){
            token = prox_token();
         //   printf("\nToken lido %s\n",token);
            continua_busca_token =classifica(token,TS);
      //      printf("\nContador posicao: %d\n",contador_posicao);
        }
        rotulos_linha = 0;
        contador_linha++;
        free(linha);
    }
}
/*classifica retorna se achou rotulos (TRUE) ou diretivas/instrucoes (FALSE)
Essas informacoes vao definir se eh necessario continuar avaliando os tokens
da linha ou se ja chegou no campo de operandos*/
int classifica(char* tok,TabelaDeSimbolos** TS){
    if(existe_token(tok)){
        if(existe_rotulo(tok)){
            if(passagem==1)
                busca_primeira_passagem(tok,TS);
            //printf("%s eh rotulo!\n",tok);
            return TRUE;
        }else if(!existe_instrucao(tok)){
            if(!existe_diretiva(tok)){
                printf("\nOperacao %s nao identificada na linha %d\n",tok,contador_linha);
            }
        }
    }
    return FALSE;
}
int existe_token(char* tok){
    return tok != NULL;
}
int existe_rotulo(char * tok){
    int ultimo_caract = tam_string(tok)-1;// -1 pois os indices vao de 0 a tamanho-1
   // printf("Ultimo caracter de %s %c, cujo tamanho eh: %d",tok,tok[ultimo_caract],sizeof(tok));
    if(tok[ultimo_caract] == ':'){// ultimo caracter valido do token eh : e primeiro nao eh numero sao os requisitos
     //   printf("Analisando rotulos\n");
        if(!eh_numero(tok[0])){
            return TRUE;
        }else{
            printf("\nRotulo %s mal formado na linha %d (rotulo nao pode comecar com numero)\n",tok,contador_linha);
        }
    }
    return FALSE;
}
int eh_numero(char c){
    return (c>='0' && c<='9');
}
int existe_instrucao(char *tok){
    if(strcmp(tok,"add")==0){
        contador_posicao+= 2;
        return TRUE;
    }else if(strcmp(tok,"sub")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"mult")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"div")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"jmp")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"jmpn")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"jmpp")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"jmpz")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"copy")==0){
        contador_posicao+=3;
        return TRUE;
    }else if(strcmp(tok,"load")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"store")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"input")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"output")==0){
        contador_posicao+=2;
        return TRUE;
    }else if(strcmp(tok,"stop")==0){
        contador_posicao+=1;
        return TRUE;
    }
    return FALSE;
}
int existe_diretiva(char *tok){
    return TRUE;
}
void busca_primeira_passagem(char* tok,TabelaDeSimbolos** TS){
    rotulos_linha++;// o montador so precisa verificar se ha mais de um simbolo
                    // por linha na primeira passagem. Se houver, um erro
                    // eh registrado e a segunda passagem nao ocorre.
    if(rotulos_linha<2){
        tok[tam_string(tok)-1] = '\0';// tira os 2 pontos do token que eh rotulo
        if(!existe_simbolo(*TS,tok)){
            *TS = InsereSimbolo(*TS,tok,contador_posicao);
        }else{
            printf("\nSimbolo %s redefinido na linha %d\n",tok,contador_linha);
        }
    }else{
        printf("\nHa mais de um rotulo na linha %d\n",contador_linha);
    }
}
