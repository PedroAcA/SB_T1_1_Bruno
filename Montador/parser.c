#include"bibliotecas_montador.h"
#include <errno.h>//usada para identificar erros de conversao erros ao usar a funcao strtol
#include <limits.h>//usada para identificar erros de conversao erros ao usar a funcao strtol
//#define FALSE 0
//#define TRUE !(FALSE)
/*a variavel rotulos_linha indica quantos rotulos existem por linha
(possibilita detectar o erro de mais de um rótulo por linha)
*/

void verifica_linhas(FILE* arq){
    int continua_busca_token;
    char *linha,*token;
    rotulos_linha = 0;
    contador_posicao=0;
    contador_linha=1;
   // printf("\nPASSAGEM: %d\n",passagem);
    while(!feof(arq)){
        linha = proxima_linha(arq);
      //  printf("\nLinha lida %s\n",linha);
        //printf("\nContador linha: %d\n",contador_linha);
        token = divide_tokens(linha);
       // printf("\nToken lido %s\n",token);
        continua_busca_token = classifica(token);
       // printf("\nContador posicao: %d\n",contador_posicao);
        while(token!=NULL && continua_busca_token){
            token = prox_token();
           // printf("\n\tToken lido %s\n",token);
            continua_busca_token =classifica(token);
         //   printf("\nContador posicao: %d\n",contador_posicao);
        }
        rotulos_linha = 0;
        contador_linha++;
        free(linha);
    }
}
/*classifica retorna se achou rotulos (TRUE) ou diretivas/instrucoes (FALSE)
Essas informacoes vao definir se eh necessario continuar avaliando os tokens
da linha ou se ja chegou no campo de operandos*/
int classifica(char* tok){
    if(existe_token(tok)){
        if(existe_rotulo(tok)){
            if(passagem==1)
                busca_primeira_passagem(tok);
            //printf("%s eh rotulo!\n",tok);
            return TRUE;
        }else if(!existe_instrucao(tok)){
            if(!existe_diretiva(tok)){
                if(passagem==1){//para nao repetir a msm msg de erro com relacao a primeira passagem
                    printf("\nOperacao %s nao identificada na linha %d\n",tok,contador_linha);
                    total_erros++;
                }
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
        if(passagem==1){// so precisa avaliar o rotulo em uma passagem so
            if(tam_string(tok)>51){// 50 caracteres de nome de variavel + 1 para ':'
                printf("\nRotulo %s com mais de 50 caracteres\n",tok);
                total_erros++;
            }else{
            //   printf("Analisando rotulos\n");
                if(eh_numero(tok[0])){
                    printf("\nRotulo %s mal formado na linha %d (rotulo nao pode comecar com numero)\n",tok,contador_linha);
                    total_erros++;
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}
int eh_numero(char c){
    return (c>='0' && c<='9');
}
void busca_primeira_passagem(char* tok){
    rotulos_linha++;// o montador so precisa verificar se ha mais de um simbolo
                    // por linha na primeira passagem. Se houver, um erro
                    // eh registrado e a segunda passagem nao ocorre.
    if(rotulos_linha<2){
        tok[tam_string(tok)-1] = '\0';// tira os 2 pontos do token que eh rotulo
        if(existe_simbolo(TS,tok)==NULL){//existe_simbolo() vai buscar o endereco do delemnto da tabeladesimbolos que tem o token. Se na ha tal elemento, retona NULL
          //  printf("\nInserindo %s na tabela de simbolos\n",tok);
            TS = InsereSimbolo(TS,tok,contador_posicao);
        }else{
            printf("\nSimbolo %s redefinido na linha %d\n",tok,contador_linha);
            total_erros++;
        }
    }else{
        printf("\nHa mais de um rotulo na linha %d\n",contador_linha);
        total_erros++;
    }
}

int existe_instrucao(char *tok){
    TabelaDeInstrucoes* instrucao_atual = busca_incrementa_posicao(tok);
    short int endereco_args[2],indice_vetor[2];//endereco_args= lista dos enderecos de memoria dos argumentos presentes na linha analisada
    if(instrucao_atual!=NULL){//OBS: adicionar funcionalidades de segunda passagem depois
        if(passagem==2){
            tok = prox_token();
            converte_em_enderecos(tok,instrucao_atual,indice_vetor,endereco_args);
            if(!existe_token(prox_token())){
                //if(!existe_argumento_externo()){
                    if(enderecos_sem_erros(instrucao_atual->mnemonico,endereco_args,indice_vetor)){
                        escreve_instrucao(instrucao_atual,endereco_args);
                        //printf("Tudo correto com a instrucao %s de argumentos %d e %d\n",instrucao_atual->mnemonico,endereco_args[0],endereco_args[1]);
                    }
                //}else{
                    //if(endereco_nao_externo_sem_erro(instrucao_atual->mnemonico,endereco_args,indice_vetor))
                        //escreve_instrucao();
                //}
            }else{
                    printf("Numero incorreto de argumentos para a instrucao %s na linha %d\n",instrucao_atual->mnemonico,contador_linha);
                    total_erros++;
            }
        }
        return TRUE;
    }
    return FALSE;
}
/*A funcao incrementa_posicao busca se a instrucao eh valida e, se for,
  atualiza o contador_posicao. Retorna TRUE(definido em pre_processador.h)
  se instrucao for valida ou FALSE (definido em pre_processador.h) caso
  contrario*/
TabelaDeInstrucoes* busca_incrementa_posicao(char*tok){
    // a funcao busca_instrucao esta definida em tabelas.c
    // a tabela de instrucoes esta declarada em bibliotecas_montador.h
    TabelaDeInstrucoes* buscador = busca_instrucao(Instrucoes,tok);// endereco de onde esta a instrucao na tabela de instrucoes (se esta existir)
    if(buscador!=NULL){
        contador_posicao+= buscador->tamanho;
    }
    return buscador;
}
int existe_diretiva(char *tok){
    short int numero=0;//guarda informacoes da constante da diretiva CONST ou numero de espacos da diretiva space
    if(strcmp(tok,"section")==0){//avalia diretivas section somente uma vez (na primeira passagem)
        tok = prox_token();
        if(strcmp(tok,"data")==0){//secao de dados
            endereco_dados = contador_posicao;// manter o endereco inical da secao de dados possibilita saber se ha pulos
                                              //para secao indevida
        }else if(strcmp(tok,"text")!=0){// a diretiva eh section, mas os argumentos nao sao data ou text
            printf("\nArgumentos da diretiva section invalidos na linha %d (diretiva section aceita somente text ou data como argumentos)\n",contador_linha);
            total_erros++;
        }
        tok = prox_token();
        if(existe_token(tok)){//diretiva section tem mais de um operando. Entao erro
            printf("\nDiretiva section tem mais de um argumento na linha %d \n",contador_linha);
            total_erros++;
        }
        return TRUE;
    }else if(strcmp(tok,"space")==0){
        tok = prox_token();
        if(existe_token(tok)){
            numero= converte_em_num(tok,numero);
            if(numero>=0){
                Tab_Dir=insereDiretiva(Tab_Dir,contador_posicao,'E',numero);
                contador_posicao+=numero;
            }else{
                printf("\nTotal de espacos a alocar menor que 0 ou erro na constante numerica na linha %d\n",contador_linha);
                total_erros++;
            }
        }else{
            numero=1;
            Tab_Dir=insereDiretiva(Tab_Dir,contador_posicao,'E',1);
            contador_posicao++;
        }
        if(passagem==2)
            escreve_diretiva('E',numero);
        return TRUE;
    }else if(strcmp(tok,"const")==0){
        tok = prox_token();
        if(existe_token(tok)){
            numero = converte_em_num(tok,numero);
            Tab_Dir=insereDiretiva(Tab_Dir,contador_posicao,'C',numero);
            contador_posicao++;
        }else{
            printf("\nDiretiva const sem constante numerica na linha %d",contador_linha);
            total_erros++;
        }
        if(passagem==2)
            escreve_diretiva('C',numero);

        return TRUE;
    }else if(strcmp(tok,"public")==0){
        return TRUE;
    }else if(strcmp(tok,"extern")==0){
        return TRUE;
    }else if(strcmp(tok,"begin")==0){
        fechou_begin_end = FALSE;
        return TRUE;
    }else if(strcmp(tok,"end")==0){
        fechou_begin_end = TRUE;
        return TRUE;
    }
    return FALSE;
}
int existe_erro_conversao(long int numero, char*tok,char*aux_erro,int erno){
    return (aux_erro == tok || *aux_erro!= '\0' ||
            ((numero == LONG_MIN || numero == LONG_MAX) && erno == ERANGE));
}
