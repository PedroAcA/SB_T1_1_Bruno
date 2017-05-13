//arquivo criado para processar algumas etapas da segunda passagem
#include"bibliotecas_montador.h"
#include <errno.h>//usada para identificar erros de conversao erros ao usar a funcao strtol
#include <limits.h>//usada para identificar erros de conversao erros ao usar a funcao strtol
// assembly inventado so aceita label+nuemro e nao label-numero
// a funcao converte_em_enderecos retira a virgula se for encontado a funcao
// copy e susbtui ela pro espaco. Espera que o ultimo token seja o primeiro argumento.
char ha_externo[2];
int indice_externo;
void converte_em_enderecos(char *tok,TabelaDeInstrucoes* instrucao_atual,short int* indice_vetor,short int*args){
    int tam=0;
    indice_externo=0;
    ha_externo[0] = 'F';
    ha_externo[1] = 'F';
    if(strcmp(instrucao_atual->mnemonico,"copy")==0){
        processa_argumentos_copy(tok,indice_vetor,args);
        tok = prox_token();
    }else if(existe_token(tok)){
        indice_realocacao[tamanho_realoc-1] = contador_posicao-1;
        tamanho_realoc++;
        indice_realocacao = (short int*) realloc(indice_realocacao,tamanho_realoc*sizeof(short int));
        tam++;
        args[0] = extrai_endereco(tok,indice_vetor);
    }else if(strcmp(instrucao_atual->mnemonico,"stop")==0){//nao ha argumentos e a instrucao eh stop
          args[0] = -2;// entao colocamos -2 na posicao 0 de args para indicar stop com argumentos corretos
          indice_vetor[0] = 0;
    }
    /*while(existe_token(tok)){
            tam++;
            args = (int*)realloc(args,tam*sizeof(int));
            args[tam-1] =  extrai_endereco(tok);
            tok = prox_token();
    }*/
    //*qte_args = tam;
}
int extrai_endereco(char* tok,short int* indice_vetor){// vai pegar uma label ou label+ numero e retornar o endereco resultante
    TabelaDeSimbolos* buscador;
    int endereco;
    if(tem_aritmetica(tok)){
        endereco = converte_exp_aritmetica(tok,indice_vetor,(ha_externo+indice_externo));
    }else{
        buscador = busca_simbolo(TS,tok);
        //if(buscador->externo == 's')
            //ha_externo[indice_externo]='T';
        if(buscador!=NULL){
            endereco = buscador->valor;
        }else{
            endereco = -1;
            printf("\nSimbolo %s nao definido na linha %d\n",tok,contador_linha);
            total_erros++;
        }
        *indice_vetor = 0;
    }
    return endereco;
}

void processa_argumentos_copy(char* tok,short int* indice_vetor,short int* args){
    short int tam=0;
    char *copia_tok,*end_tok,*inicio_desaloc;
    copia_tok = (char*) malloc((tam_string(tok)+1)*sizeof(char));
    strcpy(copia_tok,tok);
    inicio_desaloc =  copia_tok;
    if(strchr(copia_tok,',')!=NULL){
        copia_tok = elimina_caracter(tok,",");// testar para ve se strok funciona apos essa sepacacao
        copia_tok = strtok_r(copia_tok," ",&end_tok);
        while(existe_token(copia_tok) && (strchr(copia_tok,',')==NULL) ){// pra copy ser valido so pode ter uma virgula no espaco dos argumentos
            tam++;
            // para o primeiro argumento, o contador de posicao eh contador_posicao-2. Como tam vai de 1 a 2, a relacao contador_posicao-2+(tam-1) da a posicao do codigo objeto de cada argumento de copy
            indice_realocacao[tamanho_realoc-1] = contador_posicao-2+(tam-1);
            tamanho_realoc++;
            indice_realocacao = (short int*) realloc(indice_realocacao,tamanho_realoc*sizeof(short int));
            //indice_externo = tam-1;
            args[tam-1]=extrai_endereco(copia_tok,(indice_vetor+tam-1));
            copia_tok = strtok_r(NULL," ",&end_tok);
        }
        erros_args_copy(tam);
    }else{
        printf("\nFormato dos argumentos de copy incorreto na linha %d\n",contador_linha);
        total_erros++;
    }
    free(inicio_desaloc);
}
void erros_args_copy(short int n_args){
    if(n_args <2){//gera o numero de argumentos lidos para copy
        printf("\nNumero de argumentos menor do que o esperado para copy na linha %d\n",contador_linha);
        total_erros++;
    }else if(n_args>2){
        printf("\nNumero de argumentos maior do que o esperado para copy na linha %d\n",contador_linha);
        total_erros++;
    }
}
int enderecos_sem_erros(char *nome_instr,short int* enderecos,short int*indices){
    short int end_base[2],i;
    TabelaDeDiretivas* buscador;
    for(i=0;i<2;i++){
        end_base[i] = enderecos[i] - indices[i];
    }
     buscador =  busca_end_incial(Tab_Dir,end_base[0]);
    if(strcmp(nome_instr,"copy")==0 && buscador!=NULL){
        return argumentos_copy_corretos(buscador,indices,end_base);
    }else if(eh_pulo(nome_instr)){
        return pulo_valido(enderecos[0]);
    }else if (strcmp(nome_instr,"stop")==0){
        tem_stop=TRUE;
        return endereco_stop_correto(enderecos[0]);
    }else{
        if(buscador!=NULL){
            if(acessa_memoria(nome_instr)){// todas as instrucoes que acessam a memoria, a execessao do copy
                return endereco_acesso_memoria_valido(buscador,indices,0);
            }else if(strcmp(nome_instr,"div")==0){//n se pode dividir por 0
                return (divide_zero(buscador)==FALSE);
            }else{
                return endereco_alocado(buscador,indices,0);
            }
        }else{
            printf("Endereco nao reservado como constante ou espaco na linha %d\n",contador_linha);
            total_erros++;
        }
    }
    return FALSE;
}
int eh_constante(TabelaDeDiretivas* diretiva_atual){
    return (diretiva_atual->tipo == 'C');
}
int memoria_alocada(TabelaDeDiretivas* diretiva_atual,int indice){
    return indice < diretiva_atual->valor;
}
int eh_pulo(char *instrucao){
    return (strcmp(instrucao,"jmp")==0 ||strcmp(instrucao,"jmpn")==0
            || strcmp(instrucao,"jmpp")==0 || strcmp(instrucao,"jmpz")==0);
}
int acessa_memoria(char *instrucao){
    return (strcmp(instrucao,"store")==0 ||strcmp(instrucao,"input")==0);
}
int endereco_acesso_memoria_valido(TabelaDeDiretivas* buscador,short int* indices,int ind_arg){
    if(!eh_constante(buscador)){
        return endereco_alocado(buscador,indices,ind_arg);
    }else{
        printf("Tentiva de modificar um valor constante na linha %d\n",contador_linha);
        total_erros++;
    }
    return FALSE;
}
int endereco_alocado(TabelaDeDiretivas* buscador,short int* indices,int ind_arg){
    if(memoria_alocada(buscador,indices[ind_arg])){
            return TRUE;
    }else{
            printf("Endereco nao alocado para vetor na linha %d\n",contador_linha);
            total_erros++;
    }
    return FALSE;
}
int argumentos_copy_corretos(TabelaDeDiretivas* buscador, short int* indices, short int* end_base){
    if(endereco_alocado(buscador,indices,0)){
        buscador = busca_end_incial(Tab_Dir,end_base[1]);
        if(buscador!=NULL)// existe o segundo argumento
            return endereco_acesso_memoria_valido(buscador,indices,1);
        else
            return FALSE;
    }else{
        return FALSE;
    }
}
int endereco_stop_correto(int endereco){
    if(endereco==-2){//flag para indicar que nao foi dado argumento para stop
        return TRUE;
    }else{
        printf("Instrucao stop com argumentos na linha %d\n",contador_linha);
        total_erros++;
        return FALSE;
    }
}
int divide_zero(TabelaDeDiretivas* buscador){
    return(buscador->tipo=='C' && buscador->valor==0);
}
int pulo_valido(int endereco_total){
    if(endereco_dados!=-1){
        return endereco_total<endereco_dados;
    }else{
        return TRUE;// se nao ha secao de dados, entao todo codigo eh secao texto
    }
}


