#include "funcoes.h"

void liga(FILE* arq, FILE* arq2, FILE* arq3,char* nome_arq){
	FILE* arq4 = fopen(nome_arq,"w");
	char c;
	char nome[50];
	int valor, fc2, fc3, erros = 0;
	Tabela *TabelaUso1 = NULL, *TabelaUso2=NULL, *TabelaDefinicoes1=NULL, *TabelaDefinicoes2 = NULL, *TabelaUso3=NULL, *TabelaDefinicoes3=NULL, *TabelaGlobal = NULL,*p;
	Relocacao* TabelaRelocacao1 = NULL, *TabelaRelocacao2 = NULL, *TabelaRelocacao3 = NULL;
	Codigo* Codigo1 = NULL, *Codigo2 = NULL, *Codigo3 = NULL, *q;

	//COLOCA TODAS AS INFORMACOES DO PRIMEIRO ARQUIVO OBJETO EM MEMORIA
	TabelaUso1 = CriaUso(TabelaUso1,arq);
	TabelaDefinicoes1 = CriaDefinicoes(TabelaDefinicoes1,arq);
	TabelaRelocacao1 = CriaRelocacao(TabelaRelocacao1, arq);
	Codigo1 = CriaCodigo (Codigo1, arq);

	//COLOCA TODAS AS INFORMACOES DO SEGUNDO ARQUIVO OBJETO EM MEMORIA E APLICA FATOR DE CORRECAO
	TabelaUso2 = CriaUso(TabelaUso2,arq2);
	TabelaDefinicoes2 = CriaDefinicoes(TabelaDefinicoes2,arq2);
	TabelaRelocacao2 = CriaRelocacao(TabelaRelocacao2, arq2); 
	Codigo2 = CriaCodigo (Codigo2, arq2);
	fc2 = tamanho(Codigo1) +1;
	for (q = Codigo2; q!=NULL; q=q->prox){
		q->byte = q->byte+fc2;
	}
	for(p = TabelaDefinicoes2;p!=NULL;p=p->prox){
		p->valor = p->valor+fc2;
	}

	//SE EXISTE ARQUIVO OBJETO 3
	if(arq3!=NULL){ //COLOCA TODAS AS INFORMACOES DO TERCEIRO ARQUIVO OBJETO EM MEMORIA E APLICA FATOR DE CORRECAO
		TabelaUso3 = CriaUso(TabelaUso3,arq3);
		TabelaDefinicoes3 = CriaDefinicoes(TabelaDefinicoes3,arq3);
		TabelaRelocacao3 = CriaRelocacao(TabelaRelocacao3, arq3);
		Codigo3 = CriaCodigo (Codigo3, arq3);
		fc3 = fc2 + tamanho(Codigo2) + 1;
		for (q = Codigo3; q!=NULL; q=q->prox){
			q->byte = q->byte+fc3;
		}
		for(p = TabelaDefinicoes3;p!=NULL;p=p->prox){
			p->valor = p->valor+fc3;
		}
	}

	//VERIFICA SIMBOLOS INDEFINIDOS OU REDEFINICOES E CRIA TABELA DE DEFINICOES GLOBAL
	if ((AnalisaIndefinicoes(TabelaUso1,TabelaUso2,TabelaUso3,TabelaDefinicoes1,TabelaDefinicoes2,TabelaDefinicoes3) == SUCESSO) && (AnalisaRedefinicoes(TabelaDefinicoes1,TabelaDefinicoes2,TabelaDefinicoes3) == SUCESSO)){
		TabelaGlobal = CriaGlobal(TabelaGlobal,TabelaDefinicoes1,TabelaDefinicoes2,TabelaDefinicoes3);
		printf("\nPARABENS CHAMPS\n");
	}

	//TODO: RESOLVER OS CONFLITOS CRUZADOS E REALOCAR O RESTANTE DO CODIGO

	
	ImprimirCoidgo(Codigo1,Codigo2,Codigo3);

	fclose(arq4);

}

Tabela* InsereTabela (Tabela* tabela, char nome[], int valor ){ //INSERE UMA INFORMACAO NUMA TABELA DE DEFINICOES OU USO
    Tabela * novo = (Tabela*) malloc(sizeof(Tabela));
    strcpy(novo->nome, nome);
    novo->valor = valor;
    novo->prox = tabela;
    tabela = novo;
    return tabela;
}

Relocacao* InsereRelocacao (Relocacao* tabela, int byte ){ //INSERE UMA INFORMACAO NUMA TABELA DE RELOCACAO
    Relocacao *p = tabela;
    Relocacao * novo = (Relocacao*) malloc(sizeof(Relocacao));
    novo->byte = byte;
    novo->prox = NULL;
    if(p==NULL){
    	return novo;	
    }else{   
	    while (p->prox!=NULL){
	    	p=p->prox;
	    }
	    p->prox = novo;
	}
    return tabela;
}

Codigo* InsereCodigo (Codigo* tabela, int byte, int info ){ //INSERE UMA INFORMACAO NUMA TABELA DE CODIGOS
    Codigo *p = tabela;
    Codigo * novo = (Codigo*) malloc(sizeof(Codigo));
    novo->byte = byte;
    novo->info = info;
    novo->relocado = 0;
    novo->prox = NULL;
    if(p==NULL){
    	return novo;	
    }else{   
	    while (p->prox!=NULL){
	    	p=p->prox;
	    }
	    p->prox = novo;
	}
    return tabela;
}


Tabela* CriaUso (Tabela* TabelaUso, FILE* arq){ //CRIA A TABELA DE USOS A PARTIR DE UM ARQUIVO
	char nome[50];
	int valor;
	Tabela *p;

	fgets(nome,50,arq); //PEGA O TRECHO TABLE USE

	fscanf(arq,"%s",nome);
	while (strcmp(nome,"TABLE") != 0){
		fscanf(arq,"%d",&valor);
		//printf("Nome: %s, valor: %d\n",nome,valor);
		TabelaUso = InsereTabela(TabelaUso,nome,valor);
		fscanf(arq,"%s",nome);
	}
	
	//for(p = TabelaUso;p!=NULL;p=p->prox){
	//	printf("Nome: %s, valor: %d\n",p->nome,p->valor);
	//}
	fscanf(arq,"%s",nome); //PEGA O DEFINITION

	return TabelaUso;
}

Tabela* CriaDefinicoes (Tabela* TabelaDefinicoes, FILE* arq){ //CRIA A TABELA DE DEFINICOES A PARTIR DE UM ARQUIVO
	char nome[50];
	int valor;
	Tabela *p;

	fscanf(arq,"%s",nome);
	while (strcmp(nome,"TABLE") != 0){
		fscanf(arq,"%d",&valor);
		//printf("Nome: %s, valor: %d\n",nome,valor);
		TabelaDefinicoes = InsereTabela(TabelaDefinicoes,nome,valor);
		fscanf(arq,"%s",nome);
	}

	//for(p = TabelaDefinicoes;p!=NULL;p=p->prox){
	//	printf("Nome: %s, valor: %d\n",p->nome,p->valor);
	//}

	fscanf(arq,"%s",nome); //PEGA O RELOCATION

	return TabelaDefinicoes;

}

Relocacao* CriaRelocacao (Relocacao* TabelaRelocacao, FILE* arq){ //CRIA A TABELA DE RELOCACAO A PARTIR DE UM ARQUIVO
	char nome[50];
	int valor;
	char c;
	Relocacao *p;

	do{
		fscanf(arq,"%d",&valor);			
		fscanf(arq,"%c",&c);
		//printf("%d ",valor);
		TabelaRelocacao = InsereRelocacao(TabelaRelocacao, valor);
	}while (c!='\n');

	//for(p = TabelaRelocacao;p!=NULL;p=p->prox){
	//	printf("%d ",p->byte);
	//}	

	fscanf(arq,"%s",nome); //PEGA O CODE

	return TabelaRelocacao;
}

Codigo* CriaCodigo(Codigo* codigo, FILE* arq){ //CRIA UMA TABELA COM O CODIGO A PARTIR DE UM ARQUIVO
	int valor, byte=0;
	Codigo* p;


	while(!feof(arq)){
			fscanf(arq,"%d",&valor);			
			//printf("%d ",valor);
			codigo = InsereCodigo(codigo, byte, valor);
			byte++;
		}

	//for(p = codigo;p!=NULL;p=p->prox){
	//	printf("byte: %d, valor: %d\n",p->byte,p->info);
	//}
		

	return codigo;

}

int tamanho (Codigo* codigo){ //RETORNA O TAMANHO EM BYTES DE UM CODIGO
	Codigo *p = codigo;
	while(p->prox!=NULL){
		p=p->prox;
	}
	return p->byte;
}

int EstaNa (char palavra[],Tabela* tabela){ //VERIFICA SE UM ELEMENTO ESTA EM UMA TABELA
	Tabela *p = tabela;
	while(p!=NULL && (strcmp(palavra,p->nome) != 0)){
		p = p->prox;
	}

	if(p==NULL){
		return 0;
	}
	else{
		return 1;
	}
}


//ANALISA SE ALGUM ELEMENTO FOI USADO SEM SER DEFINIDO
int AnalisaIndefinicoes(Tabela* TabelaUso1,Tabela* TabelaUso2,Tabela *TabelaUso3,Tabela *TabelaDefinicoes1,Tabela* TabelaDefinicoes2,Tabela* TabelaDefinicoes3){
	int erros = 0;
	Tabela* p;

	for(p = TabelaUso1; p!=NULL; p=p->prox){
		if ( !(EstaNa(p->nome,TabelaDefinicoes2)) && (TabelaUso3 == NULL) ){
			printf("Erro de ligacao: Simbolo %s nao encontrado.\n",p->nome);
			erros++;

		}
		else if( !(EstaNa(p->nome,TabelaDefinicoes2)) && (TabelaUso3 != NULL) && !(EstaNa(p->nome,TabelaDefinicoes3)) ){
			printf("Erro de ligacao: Simbolo %s nao encontrado.\n",p->nome);
			erros++;
		}

	}

	for(p = TabelaUso2; p!=NULL; p=p->prox){
		if ( !(EstaNa(p->nome,TabelaDefinicoes1)) && (TabelaUso3 == NULL) ){
			printf("Erro de ligacao: Simbolo %s nao encontrado.\n",p->nome);
			erros++;

		}
		else if( !(EstaNa(p->nome,TabelaDefinicoes1)) && (TabelaUso3 != NULL) && !(EstaNa(p->nome,TabelaDefinicoes3)) ){
			printf("Erro de ligacao: Simbolo %s nao encontrado.\n",p->nome);
			erros++;
		}
	}

	if(TabelaUso3 != NULL){
		for(p = TabelaUso3; p!=NULL; p=p->prox){
			if( !(EstaNa(p->nome,TabelaDefinicoes1)) && !(EstaNa(p->nome,TabelaDefinicoes2)) ){
				printf("Erro de ligacao: Simbolo %s nao encontrado.\n",p->nome);
				erros++;
			}
		}
	}

	if (erros == 0)
		return SUCESSO;
	else
		return FALHA;
}

//VERIFICA SE ALGUM ELEMENTO NAO POSSUI MAIS DE UMA DEFINICAO
int AnalisaRedefinicoes(Tabela *TabelaDefinicoes1,Tabela* TabelaDefinicoes2,Tabela* TabelaDefinicoes3){
	int erros = 0;
	Tabela *p;
	for (p = TabelaDefinicoes1; p!=NULL; p=p->prox){
		if (EstaNa(p->nome, TabelaDefinicoes2) || ((TabelaDefinicoes3 != NULL) && (EstaNa(p->nome, TabelaDefinicoes3)))){
			printf("Erro de ligacao: Simbolo %s redefinido.\n",p->nome);
			erros++;
		}
	}

	for (p = TabelaDefinicoes2; p!=NULL; p=p->prox){
		if (((TabelaDefinicoes3 != NULL) && (EstaNa(p->nome, TabelaDefinicoes3)))){
			printf("Erro de ligacao: Simbolo %s redefinido.\n",p->nome);
			erros++;
		}
	}

	if (erros == 0)
		return SUCESSO;
	else
		return FALHA;
}

Tabela* CriaGlobal (Tabela* TabelaGlobal, Tabela* TabelaDefinicoes1,Tabela* TabelaDefinicoes2,Tabela* TabelaDefinicoes3){
	Tabela *p;
	for (p = TabelaDefinicoes1; p!=NULL; p=p->prox){
		TabelaGlobal = InsereTabela(TabelaGlobal,p->nome,p->valor);
	}
	for (p = TabelaDefinicoes2; p!=NULL; p=p->prox){
		TabelaGlobal = InsereTabela(TabelaGlobal,p->nome,p->valor);
	}
	for (p = TabelaDefinicoes3; p!=NULL; p=p->prox){
		TabelaGlobal = InsereTabela(TabelaGlobal,p->nome,p->valor);
	}

	return TabelaGlobal;
}

void ImprimirCoidgo(Codigo* Codigo1,Codigo* Codigo2,Codigo* Codigo3){
	Codigo *p;
	for(p = Codigo1; p!=NULL; p=p->prox){
		printf("Byte: %d: %d\n",p->byte,p->info);
	}

	for(p = Codigo2; p!=NULL; p=p->prox){
		printf("Byte: %d: %d\n",p->byte,p->info);
	}

	for(p = Codigo3; p!=NULL; p=p->prox){
		printf("Byte: %d: %d\n",p->byte,p->info);
	}
}