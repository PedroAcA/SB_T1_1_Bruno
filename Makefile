#ROOT_DIR = ${PWD}
#DIR_M = ${ROOT_DIR}/Montador 
#DIR_L = ${ROOT_DIR}/Ligador

# gedit ${ROOT_DIR}/Montador/parser.c
SOURCES_MONTADOR = arquivos.c montador.c parser.c parser2.c pre_processador.c scanner.c tabelas.c
SOURCES_LIGADOR = funcoes.c main.c
projeto: 
	@make montar --no-print-directory && make ligar --no-print-directory

montar: 
	@cd Montador && echo "\nAbrindo pasta Montador\n" && gcc -Wall -o montador $(SOURCES_MONTADOR) -I.
ligar:
	@cd Ligador && echo "\nAbrindo pasta Ligador\n" && gcc -Wall -o ligador $(SOURCES_LIGADOR) -I.	
