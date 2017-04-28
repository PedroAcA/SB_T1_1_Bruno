#include"bibliotecas_montador.h"

void preprocessamento (FILE * arq){
    FILE *pre = fopen("teste1.pre","w") ;
    char c;

    while((c = fgetc(arq)) != EOF){
        if (c!= ';'){
            c = tolower(c);
            fprintf(pre,"%c",c);
        }
        else{
            while (fgetc(arq) != '\n' );
            fprintf(pre,"\n");
        }
    }
    fclose(pre);
}

char * proxima_linha(FILE * arq){//assume que o arquivo ja esta aberto
    char *palavra,copia;
    char caracter;
    int tam_palavra,i;
    if(!feof(arq)){
        fscanf(arq,"%s",&palavra);
    }
    tam_palavra = tam_string(palavra);
    copia = palavra;
    palavra = (char *)malloc(tam_palavra*sizeof(char));
    strcpy(palavra,copia);
    for(i=0;i<tam_palavra;i++){
        caracter= tolower(palavra[i]);
        palavra[i] = caracter;
    }
    return palavra;
}
char* divide_tokens(char *linha){
    if(tem_char(linha,';')){// procura primeiro por caracteres de comentarios
        linha = strtok(linha,";");// exclui as linhas de comentarios
      //  linha[tam_string(linha) -1] = '\0';
    }
    return strtok(linha," ");//subvide a string em tokens

}
// funcao prox_token espera que a palavra ja tenha sido dividida em tokens!
char* prox_token(){
    return strtok(NULL," ");

}

/*tam_string retorna o numero de elementos em uma string*/
int tam_string(char* str){
    /*A funcao sizeof() retorna o numero de bytes que um vetor ou variavel
    ocupa na memoria. Se esse numero for dividido pelo numero de bytes que
    um caracter ocupa na memoria, entao teremos o total de elementos da string*/
    return (sizeof(str)/sizeof(char) );
}
int tem_char(char *palavra,char caract){
    return (strchr(palavra,caract)!=NULL);
}
