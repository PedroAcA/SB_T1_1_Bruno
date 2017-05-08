//arquivo criado para processar algumas etapas da segunda passagem
#include"bibliotecas_montador.h"
#include <errno.h>//usada para identificar erros de conversao erros ao usar a funcao strtol
#include <limits.h>//usada para identificar erros de conversao erros ao usar a funcao strtol
// assembly inventado so aceita label+nuemro e nao label-numero
// a funcao converte_em_enderecos retira a virgula se for encontado a funcao
// copy e susbtui ela pro espaco. Espera que o ultimo token seja o primeiro argumento.
int* converte_em_enderecos(char *tok,TabelaDeInstrucoes* instrucao_atual,int* qte_args){
    int *args;
    int tam=0;
//    char *copia_tok,*end_tok,*inicio_desaloc;
    args = (int*)malloc(sizeof(int));
    if(strcmp(instrucao_atual->mnemonico,"copy")==0){
        args = processa_argumentos_copy(tok,&tam,args);
        tok = prox_token();
    }
    while(existe_token(tok)){
            tam++;
            args = (int*)realloc(args,tam*sizeof(int));
            args[tam-1] =  extrai_endereco(tok);
            tok = prox_token();
    }
    *qte_args = tam;
    return args;
}
int extrai_endereco(char* tok){// vai pegar uma label ou label+ numero e retornar o endereco resultante
    TabelaDeSimbolos* buscador;
    int endereco;
    if(tem_aritmetica(tok)){
        endereco = converte_exp_aritmetica(tok);
    }else{
        buscador = existe_simbolo(TS,tok);
        if(buscador!=NULL){
            endereco = buscador->valor;
        }else{
            endereco = -1;
            printf("\nSimbolo %s nao definido na linha %d\n",tok,contador_linha);
            total_erros++;
        }
    }
    return endereco;
}

int tem_aritmetica(char* tok){
    return(strchr(tok,'+')!=NULL);
}
//funcao converte_exp_artimetica usa strtok_r para nao perder a referencia
    // do proximo token com relacao ao token original da linha lida
int converte_exp_aritmetica(char* tok){
    int numero=0;
    long int str_p_num;
    char *copia_tok = (char*) malloc((tam_string(tok)+1)*sizeof(char));
    char* end_tok,*inicio_desaloc,*aux_erro;//o inicio da string copia tem q se salvo pois a funcao strtok_r muda o endereco de copia_tok a cada passagem
    TabelaDeSimbolos* buscador;
    strcpy(copia_tok,tok);
    inicio_desaloc = copia_tok;
    copia_tok = elimina_caracter(copia_tok,"+");
    copia_tok =strtok_r(copia_tok," ",&end_tok);// como houve experessoes como v+1, tem q retokenizar a string
    if(existe_token(copia_tok)){//inicio da avaliacao do rotulo
            buscador = existe_simbolo(TS,copia_tok);
        if(buscador!=NULL){
            numero+= buscador->valor;
            copia_tok = strtok_r(NULL," ",&end_tok);
            if(existe_token(copia_tok)){// inicio da avalicao do numero
                errno=0;
                str_p_num = strtol(copia_tok,&aux_erro,0);
                if(!existe_erro_conversao(str_p_num,copia_tok,aux_erro,errno)){
                    numero+= (int)str_p_num;
                }else{
                    printf("\nErro na contante numerica de vetor na linha %d\n",contador_linha);
                    numero=-1;
                    total_erros++;
                }
            }else{
                printf("\nErro na formacao do endereco do vetor %s na linha %d \n",tok,contador_linha);
                total_erros++;
            }
        }else{
            printf("\nSimbolo %s nao definido na linha %d\n",copia_tok,contador_linha);
            numero = -1;
            total_erros++;
        }
    }else{
        printf("\nExpressao %s invalida na linha %d \n",tok,contador_linha);
        total_erros++;
    }
    free(inicio_desaloc);
    return numero;
}
int* processa_argumentos_copy(char* tok,int* tamanho,int* args){
    int tam=*tamanho;
    char *copia_tok,*end_tok,*inicio_desaloc;
    copia_tok = (char*) malloc((tam_string(tok)+1)*sizeof(char));
    strcpy(copia_tok,tok);
    inicio_desaloc =  copia_tok;
    if(strchr(copia_tok,',')!=NULL){
        copia_tok = elimina_caracter(tok,",");// testar para ve se strok funciona apos essa sepacacao
        copia_tok = strtok_r(copia_tok," ",&end_tok);
        while(existe_token(copia_tok)){
            tam++;
            args = (int*)realloc(args,tam*sizeof(int));
            args[tam-1]=extrai_endereco(copia_tok);
            copia_tok = strtok_r(NULL," ",&end_tok);
        }
        if((tam - *tamanho) <2){//gera o numero de argumentos lidos para copy
            printf("\nNumero de argumentos menor do que o esperado para copy na linha %d\n",contador_linha);
            total_erros++;
        }else if((tam - *tamanho)>2){
            printf("\nNumero de argumentos maior do que o esperado para copy na linha %d\n",contador_linha);
            total_erros++;
        }
    }else{
        printf("\nFormato dos argumentos de copy incorreto na linha %d\n",contador_linha);
        total_erros++;
    }
    free(inicio_desaloc);
    *tamanho =tam;
    return args;
}
