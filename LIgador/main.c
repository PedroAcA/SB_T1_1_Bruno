#include"funcoes.h"

int main(int argc, char *argv[]) {
    FILE* arq,*arq2, *arq3;

    if(argc<3){ //Se tiver poucos argumentos
    	printf("Numero de argumentos invalido");
    }
    else if(argc==3){ //Se tiver so um arquivo objeto
	    if( (argv[1][strlen(argv[1]) - 2] == '.') && (argv[1][strlen(argv[1]) - 1] == 'o') &&
	    	(argv[2][strlen(argv[2]) - 2] == '.') && (argv[2][strlen(argv[2]) - 1] == 'e') ) {// Verifica se o formato dos arquivos é correto
	    	if((arq = fopen(argv[1], "r")) !=NULL){
	    		copia(arq,argv[2]); //Copia a entrada na saida mudando a extensao
	    	}
	    	else{
	    		printf("Arquivo objeto não encontrado\n");
	    	}
	    }
	    else{
	    	printf("Formatos de arquivos incorreto. Indique 1,2 ou 3 arquivos com extensao .o e um arquivo com extensao .e\n");
	    }
    }
    else if(argc==4){ //Se tiverem 2 arquivos objetos
    	if( (argv[1][strlen(argv[1]) - 2] == '.') && (argv[1][strlen(argv[1]) - 1] == 'o') &&
	    	(argv[2][strlen(argv[2]) - 2] == '.') && (argv[2][strlen(argv[2]) - 1] == 'o') &&
	    	(argv[3][strlen(argv[3]) - 2] == '.') && (argv[3][strlen(argv[3]) - 1] == 'e') ) {// Verifica se o formato dos arquivos é correto
		    if (((arq = fopen(argv[1], "r")) !=NULL) && ((arq2 = fopen(argv[2], "r"))  !=NULL)){
			    liga(arq,arq2,NULL,argv[3]); //Faz a ligacao entre os dois
			    fclose(arq);
			    fclose(arq2);
			}
			else{
				printf("Arquivo objeto não encontrado\n");
			}
		}
	    else{
	    	printf("Formatos de arquivos incorreto. Indique 1,2 ou 3 arquivos com extensao .o e um arquivo com extensao .e\n");
	    }
	}
	else if(argc == 5){ //Se tiverem 3 arquivos objetos
    	if( (argv[1][strlen(argv[1]) - 2] == '.') && (argv[1][strlen(argv[1]) - 1] == 'o') &&
	    	(argv[2][strlen(argv[2]) - 2] == '.') && (argv[2][strlen(argv[2]) - 1] == 'o') &&
	    	(argv[3][strlen(argv[3]) - 2] == '.') && (argv[3][strlen(argv[3]) - 1] == 'o') &&
	    	(argv[4][strlen(argv[4]) - 2] == '.') && (argv[4][strlen(argv[4]) - 1] == 'e') ) {// Verifica se o formato dos arquivos é correto
		    if (((arq = fopen(argv[1], "r")) !=NULL) && ((arq2 = fopen(argv[2], "r"))  !=NULL)  && ((arq3 = fopen(argv[3], "r"))  !=NULL)){
			    liga(arq,arq2,arq3,argv[4]); //Faz a ligacao entre os tres
			    fclose(arq);
			    fclose(arq2);
			    fclose(arq3);

			}
			else{
				printf("Arquivo objeto não encontrado\n");
			}
		}
	    else{
	    	printf("Formatos de arquivos incorreto. Indique 1,2 ou 3 arquivos com extensao .o e um arquivo com extensao .e\n");
	    }
	}
	else{// Se tiverem muitos argumentos
		printf("Numero de argumentos invalido");
	}
    return 0;
}
