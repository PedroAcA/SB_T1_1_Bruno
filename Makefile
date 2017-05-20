ROOT_DIR = ${PWD}
#DIR_M = ${ROOT_DIR}/Montador 
#DIR_L = ${ROOT_DIR}/Ligador

# gedit ${ROOT_DIR}/Montador/parser.c
SOURCES_MONTADOR = arquivos.c montador.c parser.c parser2.c pre_processador.c scanner.c tabelas.c
SOURCES_LIGADOR = funcoes.c main.c
projeto: 
	@make montar --no-print-directory && make ligar --no-print-directory

#$(addprefix $(ROOT_DIR)/Montador/, $(SOURCES_MONTADOR)) concatena o diretorio completo ate a pasta atual com /Montador e distribui esse diretorio completo para todos .c presentes em SOURCES_MONTADOR
montar: $(addprefix $(ROOT_DIR)/Montador/,$(SOURCES_MONTADOR))
	@cd Montador && echo "\nAbrindo pasta Montador\n" && gcc -Wall -o montador $(SOURCES_MONTADOR) -I. && gcc -Wall -o ../montador $(SOURCES_MONTADOR) -I.

#$(addprefix $(ROOT_DIR)/Ligador/, $(SOURCES_LIGADOR)) concatena o diretorio completo ate a pasta atual com /Ligador e distribui esse diretorio completo para todos .c presentes em SOURCES_LIGADOR
ligar: $(addprefix $(ROOT_DIR)/Ligador/,$(SOURCES_LIGADOR)) 
	@cd Ligador && echo "\nAbrindo pasta Ligador\n" && gcc -Wall -o ligador $(SOURCES_LIGADOR) -I. && gcc -Wall -o ../ligador $(SOURCES_LIGADOR) -I.	
