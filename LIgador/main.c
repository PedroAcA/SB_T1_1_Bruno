#include"funcoes.h"

int main(int argc, char *argv[]) {
    FILE* arq,*arq2, *arq3;

    if(argc<3){ //Se tiver poucos argumentos
    	printf("Numero de argumentos invalido");
    }
    else if(argc==3){
    	if((arq = fopen(argv[1], "r")) !=NULL){
    		copia(arq,argv[2]);
    	}
    	else{
    		printf("Arquivo objeto não encontrado\n");
    	}
    }
    else if(argc==4){ //Se tiver só um argumentp
	    if (((arq = fopen(argv[1], "r")) !=NULL) && ((arq2 = fopen(argv[2], "r"))  !=NULL)){
		    liga(arq,arq2,NULL,argv[3]);
		    fclose(arq);
		    fclose(arq2);
		}
		else{
			printf("Arquivo objeto não encontrado\n");
		}
	}
	else if(argc == 5){
	    if (((arq = fopen(argv[1], "r")) !=NULL) && ((arq2 = fopen(argv[2], "r"))  !=NULL)  && ((arq3 = fopen(argv[3], "r"))  !=NULL)){
		    liga(arq,arq2,arq3,argv[4]);
		    fclose(arq);
		    fclose(arq2);
		    fclose(arq3);

		}
		else{
			printf("Arquivo objeto não encontrado\n");
		}
	}
	else{
		printf("Numero de argumentos invalido");
	}
    return 0;
}
